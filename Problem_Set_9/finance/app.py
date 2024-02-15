import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime #to get the transaction time
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    try:
        user_transactions = db.execute("SELECT symbol, SUM(shares) AS total_shares, price, SUM(total) AS totalMoney FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])
        total_cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])
        cash = round(total_cash[0]["cash"],2)
        stockMoney = db.execute("SELECT SUM(total) as money FROM history WHERE user_id = ? ", session["user_id"])[0]["money"]
        totalMoney = cash + stockMoney
    except:
        user_transactions = db.execute("SELECT symbol, SUM(shares) AS total_shares, price, SUM(total) AS totalMoney FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])
        total_cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])
        cash = round(total_cash[0]["cash"],2)
        stockMoney = 0
        totalMoney = cash + stockMoney
    return render_template("index.html", data=user_transactions, cash=cash, total=totalMoney)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = (request.form.get("shares"))
        if not symbol or not shares:
            return apology("must provide input")
        try:
            int(shares)
        except ValueError:
            return apology("Enter valid amount of shares", 400)
        if int(shares) <= 0:
            return apology("share must be larger than 0")
        if not lookup(symbol):
            return apology("invalid symbol")
        stock = lookup(symbol)
        buy_value = int(shares) * stock["price"]
        userID = session["user_id"]
        user_current_Cash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]
        if user_current_Cash < buy_value:
            return apology("Not enough money")
        else:
            new_Cash = user_current_Cash - buy_value
            db.execute("UPDATE users SET cash = ? WHERE id = ?",new_Cash,userID)
            time = datetime.datetime.now()
            db.execute("INSERT INTO history (user_id, shares, symbol, price, date, total) VALUES (?,?,?,?,?,?)", userID, int(shares), symbol.upper(), stock["price"], time, buy_value)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userID = session["user_id"]
    data  = db.execute("SELECT * FROM history WHERE user_id = ?", userID)
    return render_template("history.html", data = data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        user_symbol = request.form.get("symbol")
        data = lookup(user_symbol)
        if not data:
            return apology("Invalid symbol")
        return render_template("quoted.html", data = data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")
        elif not request.form.get("password"):
            return apology("must provide password")
        elif not request.form.get("confirmation"):
            return apology("must confirm password")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must match password")

        user_name = request.form.get("username")
        user_hash = generate_password_hash(request.form.get("password"))
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", user_name, user_hash)
        except:
            return apology("username already exist")
        return redirect("/")
    elif request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol")
        if not symbol or not shares:
            return apology("must provide input")
        if int(shares) <= 0:
            return apology("share must be larger than 0")
        if not lookup(symbol):
            return apology("invalid symbol")
        userID = session["user_id"]
        user_shares = db.execute("SELECT SUM(shares) as shares FROM history WHERE user_id = ? AND symbol = ? ",userID, symbol.upper() )
        if int(shares) > user_shares[0]["shares"]:
            return apology("more shares than you have")
        stock = lookup(symbol)
        sell_value = int(shares) * stock["price"]
        user_current_Cash = db.execute("SELECT cash FROM users WHERE id = ?", userID)[0]["cash"]
        newCash = sell_value + user_current_Cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?",newCash,userID)
        time = datetime.datetime.now()
        db.execute("INSERT INTO history (user_id, shares, symbol, price, date, total) VALUES (?,?,?,?,?,?)", userID, -int(shares), symbol.upper(), stock["price"], time, -sell_value)
        return redirect("/")

    elif request.method == "GET":
        user_id = session["user_id"]
        symbols = db.execute("SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares)>0", user_id)
        return render_template("sell.html", symbols=symbols)

