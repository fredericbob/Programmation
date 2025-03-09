var express=require('express');
var app= express();

var exemple=(req,res,next)=>{
   req.exemple=Date.now();
   next();
}

app.use(exemple);
app.get('/',function(req,res){
  var responsetext='heloo';
  responsetext += responsetext +" req :" +req.exemple;
  res.send(responsetext); 
});


app.listen(3000,function(){
    console.log("Listen app 3000");
});