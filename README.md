# TC1030-Proyecto
Un servicio de streaming busca tener un control de sus contenidos para hacer más fácil su administración, el programa permite hacer actualizaciones de contenido, agregando distintos tipos de elementos, que son películas y series, permitiendo calificarlo, obtener su duración, entre otras cosas, para esto se deben considerar las diferencias entre los tipos de contenido, pues las series contienen temporadas que a su vez contienen episodios con distintas características cada uno. Se busca tener en cuenta todos estos factores para el buen manejo de estos contenidos.

# Consideraciones
El programa sólo permite actualizaciones de agregar contenido nuevo, por lo que no es posible eliminar episodios, películas, o temporadas de series. También es importante considerar que los arreglos creados están en el stack, por lo que tienen un número límite definido inicialmente, e intentar agregar demasiado contenido provocará una falla en el programa.

# Actualizaciones
Se implementaron las clases propuestas en el diagrama UML en el archivo multimedia.h

Se creó el archivo series.h para las clases Episodio y Temporada para la mejor lectura del código, también se agregaron las funciones to_string para regresar la información de cada clase, esta función se realzó como virtual en la clase Multimedia para poder reescribirla al utilizar apuntadores y hacer uso de polimorfismo. También, se agregó un main para mostrar un ejemplo de la función to_string

Se agregó interacción con el usuario para que pueda crear contenido multimedia, también se volvió a la clase Multimedia abstracta pues la plataforma solo soporta películas y series, y cada una ya cuenta con su clase. Aún faltan por implementar las funciones modifica_multimedia y modifica_plataforma

Se terminó de implementar la función modifica_plataforma y la función modifica_multimedia en menus.h

Correción de errores, se agregó la opción para crear ejemplos al inicio del programa

Se actualizó el diagrama UML conforme a los cambios hechos en las clases

Se agregaron comentarios explicando las funciones implementadas en cada uno de los archivos
