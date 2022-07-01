<h1 align="center"><i>✨ lua-huffman ✨ </i></h1>
<h3 align="center">The lua binding for <a href="https://github.com/synodriver/huffman">huffman</a> </h3>

### huffman compress and decompress for lua

- usage
```
hfm = require("hfm")

data = "1234"

for i = 1, 10 do
data = data .. data
end
print("origin len : " .. #data)
encoded = hfm.encode(data)
print("encoded len : " .. #encoded)
print(hfm.decode(encoded))

hfm.encode_file("Makefile", "Makefile.bin")
hfm.decode_file("Makefile.bin", "Makefile.txt")
```