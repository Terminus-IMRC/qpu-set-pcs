CFLAGS := -I/home/pi/.local/local/include -O2 -Wall -Wextra
LDFLAGS := -L/home/pi/.local/local/lib -lmailbox -lvc4v3d

all: qpu-set-pcs

qpu-set-pcs: qpu-set-pcs.o

.PHONY: clean
clean:
	$(RM) qpu-set-pcs
	$(RM) qpu-set-pcs.o
