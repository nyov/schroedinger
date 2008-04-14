package org.diracvideo.Schroedinger;

public class Unpack {
    private byte d[];
    private int i = 0, r, l = 0;
    
    public Unpack(byte d[]) {
	this.d = d;
	fill();
    }
    
    private void fill() {
	int b = (d.length - i >= 4 ? 3 : d.length - i - 1) * 8;
	for(; l <= b; l += 8) {
	    r |= d[i++] << (24 - l);
	}
    }
    
    public void align() {
	r <<= (l & 7);
	l -= (l & 7);
	fill();
    }

    public int bits(int n) {
	int v = 0;
	if (n > l) {
	    fill();
	} 
	v = (r >> (32 - n));
	l -= n;
	r <<= n;
	return v;
    }
    
    public int decodeUint() {
	int v = 1;
	while(bits(1) == 0) {
	    v = (v << 1) | bits(1);
	}
	return v - 1;
    }

    public int decodeSint() {
	int v = decodeUint();
	return (bits(1) == 1 ? -v : v);
    }

    public int bitsLeft() {
	return (d.length - i) * 8 + l;
    }

    public void init(byte d[], int o) {
	this.d = d;
	l = 0;
	i = o;
	fill();
    }

    public static void test() {
	String s = "Hello, World";
	byte r[] = new byte[s.length()-1];
	Unpack u = new Unpack(s.getBytes());
	u.bits(5);
	u.align();
	for(int i = 0; i < r.length && u.bitsLeft() >= 8; i++) {
	    r[i] = (byte)u.bits(8);
	}
	String o = new String(r);
	if(s.substring(1).compareTo(o) != 0) {
	    throw new Error("Something wrong with Unpack");
	}
    }

}