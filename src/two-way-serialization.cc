typedef char BYTE;

struct InputArchive {
	void read(BYTE* data, int size) {
		// implement me
	}
};

struct OutputArchive {
	void write(BYTE* data, int size) {
		// implement me
	}
};

// http://bitsquid.blogspot.se/2009/10/two-way-serialization-function.html

struct Object {
	template <typename STREAM>
	STREAM & serialize(STREAM & stream) {
		return stream & a & b & c;
	}
	int a, b, c;
};

template <typename STREAM, typename T>
STREAM & operator &(STREAM & stream, T & t) {
	t.serialize(stream);
}

template < > InputArchive & operator &(InputArchive &a, int &v) {
	a.read(reinterpret_cast<BYTE*>(&v), sizeof(v));
	return a;
}

template < > OutputArchive & operator & (OutputArchive &a, int &v) {
	a.write(reinterpret_cast<BYTE*>(&v), sizeof(v));
	return a;
}
