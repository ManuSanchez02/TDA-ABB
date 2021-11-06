![](https://i.imgur.com/P0aqOMI.jpg)

# **TDA — ABB** 


## [7541/9515] Algoritmos y Programación II


### Segundo cuatrimestre de 2021

|  Alumno: | Sanchez Fernandez de la Vega, Manuel |
| ----------- | ----------- |
| Número de padrón: | 107951 |
| Email: | msanchezf@fi.uba.ar |


#### 1. Introducción

El objetivo del TDA es implementar un arbol binario de busqueda, tambien conocido como ABB. Es un tipo de dato abstracto eficiente a la hora de realizar operaciones como busqueda, insercion o eliminacion. 

#### 2. Teoría

1. Un arbol es un tipo de dato abstracto conformado por una coleccion de nodos, los cuales estan enlazados en forma de arbol. Cada nodo tiene Hay muchos tipos de arboles, algunos mas eficientes que otros, distintas cantidades de hijos e implementaciones, etc. Por ejemplo, AVL, ABB, arbol n-ario, arbol rojo y negro, arbol B, B+ y B*, entre otros.
Un tipo de arbol son los arboles binarios, cuyos nodos unicamente tienen 2 hijos. Este tipo de dato no esta ordenado de ninguna forma y simplemente consta de una coleccion de nodos conectados arbitrariamente.
La idea de arbol binario se puede expandir un poco mas, al agregar la condicion de que los elementos mayores al elemento de cada nodo deben ir a la derecha, y los menores a la izquierda (esto es una convencion, tranquilamente se pueden poner los menores a la derecha y mayores a la izquierda). Esta condicion significa que se puede optimizar en gran forma las operaciones que se pueden realizar. De esta forma, obtenemos un ABB o arbol binario de busqueda. Al ser binario, tiene propiedades similares a la busqueda binaria. El orden de complejidad de algunas operaciones como buscar o insertar es $O(log(n))$ por lo que se puede considerar como eficiente (siempre y cuando el arbol este balanceado). Esto se debe a que aprovecha el principio de divide y conquista para optimizar las operaciones. Por ejemplo, al buscar un elemento, cada vez que se pasa por un nodo (si el arbol esta balanceado), se compara para ver si el elemento buscado es mayor, menor o igual al actual y se descarta la mitad de los mismos. 

1. La explicacion de la implementacion se encuentra en la seccion de detalles de implementacion.

#### 3. Detalles de implementación


A la hora de implementar el arbol binario de busqueda, utilice un conjunto de nodos enlazados. Estos nodos contienen 3 datos importantes:
- Un puntero a el hijo izquierdo
- Un puntero a el hijo derecho
- Un puntero al elemento

El hijo derecho de cada nodo siempre tiene un elemento mayor al del nodo, y el hijo izquierdo siempre tiene un elemento menor. Como consecuencia, queda armada una especie de arbol de nodos en la que los elementos mas grandes se encuentran por la derecha y los elementos mas chicos, por la izquierda.
Sobre este arbol de nodos se pueden realizar operaciones similares a las de una lista pero con una complejidad superior. Como ya fue mencionado en las seccion teorica, se utiliza el principio de division y conquista para lograr esta optimizacion.

Luego, el padre de todos los nodos, es decir el nodo raiz, es referenciado en una nueva estructura que definimos como arbol, cuyos campos son:
- Un puntero al nodo raiz
- La cantidad de elementos
- Una funcion para comparar los elementos

Esta ultima funcion es necesaria debido a que es posible guardar absolutamente cualquier tipo de dato en los nodos. Por ello, y como ya fue explicado previamente, el arbol realiza comparaciones constantemente. Como resultado, es necesario definir una funcion que sirva para realizar comparaciones entre 2 elementos del tipo de dato suminstrado al arbol.

En mi implementacion, hice uso de la recursividad para el desarrollo de las funciones. Esto se debe a que permite desplazarse a lo largo del arbol de una forma mucho mas sencilla e intuitiva. Sin embargo, para poder hacer que las funciones sean recursivas, es necesario que en los parametros exista uno que represente al nodo actual. En consecuencia, no queda otra alternativa que crear funciones auxiliares que en vez de tener un parametro de arbol, tenga un parametro que sea el nodo actual. Esto tiene como fin el poder hacer una llamada recursiva pero usando `nodo->izquierda` o `nodo->derecha` dependiendo que queremos hacer.

1. `abb_recorrer()`

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