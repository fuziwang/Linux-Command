objs = main.o  ctty.o

main: $(objs)

clean:
	rm $(objs) main