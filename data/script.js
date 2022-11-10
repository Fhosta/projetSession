// function getFromESP_getNom () {
//     var xhttp = new XMLHttpRequest();
//     xhttp.onreadystatechange = function () {
//     if (this.readyState == 4 && this.status == 200) {
//     document.getElementById("nom").innerHTML = this.responseText;
//     }
//     };
//     xhttp.open("GET", "getNomEsp", true);
//     xhttp.send();
//    }

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



function getFromESP_getAllWoodOptions() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var arrayOfStrings = this.responseText.split("&");
            for (i = 0; i < arrayOfStrings.length; i=i+2) {
                var x = document.getElementById("listeBois");
                var option = document.createElement("option");
                option.value = arrayOfStrings[i];
                option.text = arrayOfStrings[i+1];
                x.add(option);
                } 

            //Refresh le contenu
            var siteHeader = document.getElementById('listeBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            }
    };
    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.send();
}