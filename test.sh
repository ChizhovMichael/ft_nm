#!/bin/sh
./ft_nm $1 > out1
nm $1 > out2
diff out1 out2
