CFLAGS := -pipe -g -O2 -W -Wall -Wextra
LDFLAGS := -lvc4regmap -lbcm_host -L/opt/vc/lib

all: qpu-set-pcs

qpu-set-pcs: qpu-set-pcs.o

.PHONY: clean
clean:
	$(RM) qpu-set-pcs
	$(RM) qpu-set-pcs.o
