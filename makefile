all : cat stat cp mv rm grep chmod chown ls mkdir ps
.PHONY : clean

cat:
	gcc -o cat cat.c

stat:
	gcc -o stat stat.c

cp:
	gcc -o cp cp.c

mv:
	gcc -o mv mv.c

rm:
	gcc -o rm rm.c

grep:
	gcc -o grep grep.c

find:
	gcc -o find find.c

chmod:
	gcc -o chmod chmod.c

chown:
	gcc -o chown chown.c

ls:
	gcc -o ls ls.c

mkdir:
	gcc -o mkdir mkdir.c

ps:
	gcc -o ps ps.c


