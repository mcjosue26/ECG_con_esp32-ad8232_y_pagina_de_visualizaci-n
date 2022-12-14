var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
const mysql = require('mysql');
app.use(express.static('public'));

io.on('connection', function(socket){
	socket.on('nuevo_mensaje', function(data){
		console.log(data);
		io.sockets.emit('desde_servidor',data);
	});
	io.sockets.emit('desde_servidor',"hola");
});

server.listen(5001, function(){
	console.log('Servidor corriendo en el puerto 5001.');
	//console.log(consulta("Josue","mcjosue"));
	//if(consulta() == "Josue"){console.log("correcto")};
});
/*
function consulta(nombre,contrasena){
	var result =0;
	const conection = mysql.createConnection({
        host: 'localhost',
        user: 'root',
        password: '',
        database: 'users'
    });
    
    conection.connect( (err) =>{
        if(err) throw err
    })
    
    conection.query('SELECT * from datos', (err,rows) =>{
        if(err) throw err
        //return rows[0].nombre;
		//console.log(rows[0].nombre);
		for (var i = 0; i < rows.length; i++) {
			if(rows[i].nombre == "Josue" && rows[i].contrasena == "mcjosue"){
				result = 1;
				//console.log(result);
			};
		  }
    });
	conection.end();
	return result;
	
};*/
