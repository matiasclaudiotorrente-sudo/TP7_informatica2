Explicación del código de processing: 
Salidas (L1 y L2): son los LEDs de la placa. Se ven como círculos: L1 se pone rojo y L2 amarillo cuando están prendidos, y quedan blancos cuando están apagados. Si se hace clic sobre un círculo en el entorno de processing, el led en la protoboard se enciende, si se vuelve a hacer clic, se apaga. 
. Setup:
Se ejecuta una sola vez al empezar. Crea la ventana, busca los puertos USB conectados a la computadora y se conecta a uno. La velocidad de comunicación es de 9600, que tiene que ser la misma que use la placa.  
. Clics del mouse:
Cada vez que se hace un clic, el programa calcula si el mouse estaba sobre alguno de los círculos. Si fue así, le manda a la placa el 1 o el 2 según corresponda para prender o apagar el led correspondiente.

