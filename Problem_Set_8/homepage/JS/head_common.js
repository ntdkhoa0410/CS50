document.addEventListener("DOMContentLoaded", function() {
    fetch('common_content.html')
        .then(response => response.text())
        .then(data => {
            const head = document.head;
            const parser = new DOMParser();
            const headContent = parser.parseFromString(data, 'text/html').head;
            head.innerHTML = headContent.innerHTML + head.innerHTML;
        });
});
