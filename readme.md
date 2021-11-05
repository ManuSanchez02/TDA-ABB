
![](https://i.imgur.com/P0aqOMI.jpg)

# **Trabajo Práctico n — NombreTP** 


## [7541/9515] Algoritmos y Programación II


### Segundo cuatrimestre de 2021

|  Alumno: | Sanchez Fernandez de la Vega, Manuel |
| ----------- | ----------- |
| Número de padrón: | 107951 |
| Email: | msanchezf@fi.uba.ar |


#### 1. Introducción

El objetivo del TDA es implementar un arbol binario de busqueda, tambien conocido como ABB. Es un tipo de dato abstracto eficiente a la hora de realizar operaciones como busqueda, insercion o eliminacion. 

#### 2. Teoría

1. Un arbol es un tipo de dato abstracto conformado por una coleccion de nodos, los cuales estan enlazados en forma de arbol. Cada nodo tiene Hay muchos tipos de arboles, algunos mas eficientes que otros, distintas cantidades de hijos e implementaciones, etc. 
Un tipo de arbol son los arboles binarios, cuyos nodos unicamente tienen 2 hijos. Este tipo de dato no esta ordenado de ninguna forma y simplemente consta de una coleccion de nodos conectados arbitrariamente.
La idea de arbol binario se puede expandir un poco mas, al agregar la condicion de que los elementos mayores al elemento de cada nodo deben ir a la derecha, y los menores a la izquierda (esto es una convencion, tranquilamente se pueden poner los menores a la derecha y mayores a la izquierda). Esta condicion significa que se puede optimizar en gran forma las operaciones que se pueden realizar. De esta forma, obtenemos un ABB o arbol binario de busqueda. Al ser binario, tiene propiedades similares a la busqueda binaria. El orden de complejidad de algunas operaciones es $O(log(n))$ por lo que se puede considerar como eficiente (siempre y cuando el arbol este balanceado). Esto se debe a que aprovecha la recursividad y el principio de divide y conquista para optimizar las operaciones. Por ejemplo, al buscar un elemento, cada vez que se pasa por un nodo (si el arbol esta balanceado), se compara para ver si el elemento buscado es mayor, menor o igual al actual y se descarta la mitad de los mismos. 

2. respuesta2

#### 3. Detalles de implementación


Detalles especificos de la implementacion, como compilar, como ejecutar


1. Detalles de alguna función

    Algún detalle importante sobre alguna función.

2. Detalle de otra función

    Algún detalle de otra función.

#### 4. Diagramas

1. Diagrama1

    ![Diagrama1](https://i.imgur.com/KvYn8UD.png)

    Explicacion del diagrama1, en caso de ser necesaria.

2. Diagrama2

    ![Diagrama2](https://i.imgur.com/nhqXNr6.png)

    Explicacion del diagrama2, en caso de ser necesaria.