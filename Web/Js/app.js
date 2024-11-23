// Importer les pays depuis le fichier data.js
import { pays } from './data.js';

// Récupérer l'élément <select> avec id="pays"
const selectElement = document.getElementById("pays");

// Ajouter les options dynamiquement
pays.forEach(function(paysItem) {
    const option = document.createElement("option");
    option.value = paysItem;  // Définir la valeur de l'option
    option.textContent = paysItem;  // Définir le texte visible pour l'option
    selectElement.appendChild(option);  // Ajouter l'option au <select>
});
