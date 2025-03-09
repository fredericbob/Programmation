function processNumbers() {
    // Étape 1 : Récupérer la saisie utilisateur
    const input = document.getElementById('numberInput').value;
    
    if (!input) {
      alert('Veuillez entrer des nombres.'); // Message d'erreur si le champ est vide
      return;
    }
  
    // Étape 2 : Convertir la saisie en tableau de nombres
    const numbers = input
      .split(',') // Diviser la chaîne par les virgules
      .map(num => parseInt(num.trim())) // Supprimer les espaces et convertir en nombres
      .filter(num => !isNaN(num)); // Retirer les valeurs invalides (ex: lettres)
  
    if (numbers.length === 0) {
      alert('Veuillez entrer des nombres valides.'); // Message si aucun nombre valide
      return;
    }
  
    // Étape 3 : Préparer les données pour le premier tableau (ordre d'entrée)
    const table1Data = numbers.map(num => {
      return { 
        number: num, 
        type: num % 2 === 0 ? 'pair' : 'impair' // Vérifier si le nombre est pair ou impair
      };
    });
  
    // Étape 4 : Trier les nombres pour le second tableau
    const sortedNumbers = [...numbers].sort((a, b) => b - a); // Tri du plus grand au plus petit
  
    // Alterner entre le plus grand et le plus petit
    const alternateOrder = [];
    while (sortedNumbers.length > 0) {
      if (sortedNumbers.length > 0) alternateOrder.push(sortedNumbers.shift()); // Plus grand
      if (sortedNumbers.length > 0) alternateOrder.push(sortedNumbers.pop());   // Plus petit
    }
  
    const table2Data = alternateOrder.map(num => {
      return { 
        number: num, 
        type: num % 2 === 0 ? 'pair' : 'impair' 
      };
    });
  
    // Étape 5 : Afficher les résultats dans les tableaux
    renderTable('table1', table1Data);
    renderTable('table2', table2Data);
  }
  
  function renderTable(tableId, data) {
    // Récupérer le corps du tableau (tbody)
    const tableBody = document.getElementById(tableId).querySelector('tbody');
    tableBody.innerHTML = ''; // Vider le tableau avant d'ajouter les nouvelles lignes
  
    // Ajouter une ligne pour chaque élément
    data.forEach(row => {
      const tr = document.createElement('tr');
      tr.innerHTML = `<td>${row.number}</td><td>${row.type}</td>`; // Ajouter les colonnes
      tableBody.appendChild(tr); // Ajouter la ligne au tableau
    });
  }
  