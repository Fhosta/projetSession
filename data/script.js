var boisSelectionner;

window.addEventListener('load',()=>{
 getFromESP_getAllWood();
});

setInterval(function getlireTemp(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if(this.status == 200) {
    document.getElementById("temp").value = this.responseText;
    }
    };
    xhttp.open("GET", "getTemp", true);
    xhttp.send();
   }, 1000);


   setInterval(function getlireTempsCompteur(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if(this.status == 200) {
    document.getElementById("tempRestantCuisson").innerHTML = this.responseText;
    }
    };
    xhttp.open("GET", "getTempsCompteur", true);
    xhttp.send();
   }, 1000);

function getFromESP_getAllWood() 
{
    var xhttp = new XMLHttpRequest();
    xhttp.responseType = 'text';
    xhttp.onreadystatechange = function () {
        const responseParsed = JSON.parse(this.responseText);
        if (this.readyState == 4 && this.status == 200) {
            for(let i = 0; i < responseParsed.length; i++) {
                let currentWood = responseParsed[i].name;
                var x = document.getElementById("listeBois");
                var option = document.createElement("option");
                option.value = currentWood;
                option.text = currentWood;
                x.add(option);
            } 

            //Refresh le contenu
            var siteHeader = document.getElementById('listeBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';
        }
    };
    xhttp.open("GET", "getAllWood", true);
    xhttp.send();
}

function getFromESP_getAllWoodDetail(selectedObject) 
{
    params = selectedObject.options[selectedObject.selectedIndex].value;

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        const responseParsed = JSON.parse(this.responseText);
        if (this.readyState == 4 && this.status == 200) {
            boisSelectionner = responseParsed;
            document.getElementById("bois").innerHTML = selectedObject.options[selectedObject.selectedIndex].text;
            document.getElementById("boisCuisson").innerHTML = selectedObject.options[selectedObject.selectedIndex].text;
            document.getElementById("type").innerHTML = responseParsed.type;
            document.getElementById("origin").innerHTML = responseParsed.origine;
            document.getElementById("tempsSechage").innerHTML = responseParsed.drying + " secondes";
            document.getElementById("tempsSechageCuisson").innerHTML = "/"+responseParsed.drying + " secondes";
            document.getElementById("tempRestantCuisson").innerHTML =responseParsed.drying;
            document.getElementById("tempMin").innerHTML = responseParsed.tempMin + " °C";
            document.getElementById("tempMinCuisson").innerHTML = "(min:"+responseParsed.tempMin + " °C)";
        }
            document.getElementById("Demarrer").addEventListener("click", four);
    }

    xhttp.open("GET", "getAllWoodDetail?name=" + params, true);
    xhttp.send();
    
}

function four(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "envoyerInfo?drying="+boisSelectionner.drying+"&tempMin="+boisSelectionner.tempMin, true);
    xhttp.send();
}
