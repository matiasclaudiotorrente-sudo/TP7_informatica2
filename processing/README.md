Explicación del código de processing: 
En la ventana aparecen dos grupos de elementos:
•	Entradas (E1 y E2): son  pulsadores conectados a la placa. En la pantalla se ven como cuadrados que se ponen de color  cuando están activados y quedan en blanco  cuando no.
•	Salidas (L1 y L2): son los LEDs de la placa. Se ven como círculos: L1 se pone rojo y L2 amarillo cuando están prendidos, y quedan blancos cuando están apagados. Si se hace clic sobre un círculo en el entorno de processing, el led en la protoboard se enciende, si se vuelve a hacer clic, se apaga. 
•	Código:
. Setup:
Se ejecuta una sola vez al empezar. Crea la ventana, busca los puertos USB conectados a la computadora y se conecta a uno. La velocidad de comunicación es de 9600, que tiene que ser la misma que use la placa. 
. Recepción de datos: cuando la placa envía un mensaje con el estado de las entradas y las salidas (por ejemplo 1,0,0,1), el programa lo separa en cuatro valores y los guarda en las variables e1, e2, l1 y l2.
. Dibujo:
Se repite todo el tiempo, muchas veces por segundo, su tarea es dibujar la pantalla según los valores guardados en las variables e1, e2, l1 y l2. Si una vale 1, pinta de color; si vale 0, deja en blanco. 
. Clics del mouse:
Cada vez que hacés clic, el programa calcula si el mouse estaba sobre alguno de los círculos. Si fue así, le manda a la placa el 1 o el 2 según corresponda para prender o apagar el led correspondiente.

