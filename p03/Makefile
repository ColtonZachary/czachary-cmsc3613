p03: p03.o LazyBinarySearchTree.o
	g++ -o p03 p03.o LazyBinarySearchTree.o

p03.o: p03.cpp LazyBinarySearchTree.h TreeNode.h
	g++ -c p03.cpp

LazyBinarySearchTree.o: LazyBinarySearchTree.cpp LazyBinarySearchTree.h TreeNode.h
	g++ -c LazyBinarySearchTree.cpp

run: p03
	./p03 input.dat output.dat

clean:
	rm -f p03 *.o