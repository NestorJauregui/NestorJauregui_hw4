cuerda.gif : data.txt animacion.py
	python animacion.py

data.txt : salida.x
	./salida.x > data.txt

salida.x : cuerda.c
	gcc cuerda.c -o salida.x -lm

clean:
	rm -f salida.x data.txt
