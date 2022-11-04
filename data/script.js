function getFromESP_getNom () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
    document.getElementById("nom").innerHTML = this.responseText;
    }
    };
    xhttp.open("GET", "getNomEsp", true);
    xhttp.send();
   }

setInterval(function getlireTemp(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if(this.status == 200) {
    document.getElementById("temp").value = this.responseText;
    }
    };
    xhttp.open("GET", "lireTemp", true);
    xhttp.send();
   }, 1000);