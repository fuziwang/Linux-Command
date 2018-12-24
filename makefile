objs = cat.o chomd.o chown.o cp.o find.o grep.o ls.o mkdir.o mv.o ps.o rm.o stat.o

main: $(objs)

clean:
	rm $(objs) main