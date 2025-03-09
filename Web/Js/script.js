function number(){

    const input=document.getElementById('numberInput').value;

    const number=input.split(",").map(num=>parseInt(num.trim())).filter(num=>!isNaN(num));
    console.log(number);

    if(number.length===0){
        alert("veulliez entrer des chiffres");
        return;
    }
    const premiertableau= number.map(num=>{
        return {
            numbers:num,
            type:num % 2===0 ? 'pair' : 'impair'
        };
    });

    const tricroissant =[...number].sort((a,b)=>b-a);

    const nouveauTab=[];
   while(tricroissant.length>0){
    if(tricroissant.length>0) nouveauTab.push(tricroissant.shift());
    if(tricroissant.length>0) nouveauTab.push(tricroissant.pop());
   }
    
    const deuxiemetableau=nouveauTab.map(num=>{
        return{
            numbers:num,
            type:num%2===0? 'pair' : 'impair'
        };
    });
 
    createtable('table1',premiertableau)
    createtable('table2',deuxiemetableau)
      
}

function createtable(Idtable,data){
    const tablebody=document.getElementById(Idtable).querySelector('tbody');
    tablebody.innerHTML='';

    data.forEach(element => {
        const tr = document.createElement('tr');
        tr.innerHTML=`<td>${element.numbers}</td><td>${element.type}</td>`;
        tablebody.appendChild(tr);
        
    });

}