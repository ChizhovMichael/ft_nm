# ft_nm
The nm command displays information about symbols in the specified File, which can be an object file, an executable file, or an object-file library. If the file contains no symbol information, the nm command reports the fact, but does not interpret it as an error condition. The nm command reports numerical values in decimal notation by default.

Your program must behave like the system nm on every aspect. You have to work with ELF binaries. You have to handle x86_32, x64, object files, .so You must code in C and use a Makefile. Output is to be similar to nm on the symbols list (order, offset, padding...).

<h2>Final grade : 100/125</h2>
<p>Mandatory part : 100/100</p>
<p>Bonus part : 0/25</p>
<h3>How to use it</h3>
<p>Simply run the setup in main folder :</p>
<pre>
<code>make build && make all</code>
</pre>
