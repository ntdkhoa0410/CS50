-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find out what happened on the day the crime took place
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = "Humphrey Street";

-- Find out the interview on that day
SELECT transcript
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2021;

-- From the transcript, look for what car that left, then see their name on their license plate
SELECT bakery_security_logs.license_plate,bakery_security_logs.activity, people.name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.year = 2021
AND bakery_security_logs.minute >=15
AND bakery_security_logs.minute <= 25
AND bakery_security_logs.activity = "exit";

--Another transcrip saying that he thief withdrawn money, their for check the transaction and find that people's name
SELECT DISTINCT people.name
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.transaction_type = "withdraw"
AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.year = 2021
AND atm_transactions.atm_location = "Leggett Street";
-- From the above, The suspect might be:
-- Bruce, Diana, Iman, Luca

--Next to the phonecall hint, we will look for the caller with phonecall < 1 min on that date
SELECT DISTINCT people.name, phone_calls.caller, phone_calls.receiver
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.year = 2021
AND phone_calls.duration < 60;
--From the above table, the suspects are: Bruce and Diana

-- To the flight hint, this is to find the earliest flight that depart from FiftyVille, also find the destination of the theft:
SELECT flights.id, flights.origin_airport_id, flights.destination_airport_id, airports.city
    FROM flights
    JOIN airports ON airports.id = flights.destination_airport_id
    WHERE flights.month = 7 AND flights.day = 29 AND flights.year = 2021
    AND flights.origin_airport_id =
        (SELECT id
        FROM airports
        WHERE city = "Fiftyville")
    ORDER BY flights.hour, flights.minute
    LIMIT 1;
--From this, complete question 2 that is NY city

--So our suspects are Bruce and Diana, one of them flew to NYC. Narrow down who was the passenger on that flight:
SELECT people.name
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = 36
AND people.name IN ("Bruce", "Diana");
-- Cleary, Bruce was the one
-- Go back to the phonecall table, see his sidekick is Robin
SELECT people.name
FROM people
WHERE people.phone_number = "(375) 555-8161"