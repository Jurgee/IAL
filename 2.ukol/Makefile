run:
	cd ./btree/iter/;\
	echo "/btree/iter: ";\
	make run;\
	echo "";\
	cd ../.. ;\
	cd ./btree/rec/;\
	echo "/btree/rec: ";\
	make run;\
	echo "";\
	cd ../.. ;\
	cd ./hashtable/;\
	echo "/hashtable: ";\
	make run;\
	echo "";\

val:
	cd ./btree/iter/;\
	make;\
	cd ../.. ;\
	cd ./btree/rec/;\
	make;\
	cd ../.. ;\
	cd ./hashtable/;\
	make;\
	cd ../ ;\
	valgrind --log-file=tmp2 ./btree/iter/test >tmp ;\
	cat tmp2 ;\
	valgrind --log-file=tmp2 ./btree/rec/test >tmp ;\
	cat tmp2 ;\
	valgrind --log-file=tmp2 ./hashtable/test >tmp ;\
	cat tmp2 ;\
	rm tmp ;\
	rm tmp2 ;\

pack:
	tar cvf xstipe02.tar hashtable/hashtable.c btree/iter/btree.c btree/rec/btree.c ;\