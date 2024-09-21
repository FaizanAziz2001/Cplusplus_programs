#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

namespace mp = boost::multiprecision;


mp::cpp_bin_float_100 fermat_factorization(mp::cpp_bin_float_100 n) {

    mp::cpp_bin_float_100 a =mp::ceil(sqrt(n));
    mp::cpp_bin_float_100 b2 = a * a - n;


    while (sqrt(b2)!=mp::floor(sqrt(b2))) {
		a += 1;
		b2 = a * a - n;
	}

    mp::cpp_bin_float_100 b = sqrt(b2);
    return a - b;

}

mp::cpp_int totient(mp::cpp_int p, mp::cpp_int q) {
	return (p - 1) * (q - 1);
}

mp::cpp_int calculate_d(mp::cpp_int e, mp::cpp_int phi) {
	mp::cpp_int d = 0;
	mp::cpp_int k = 1;

    while (true) {
		d = (k * phi + 1) / e;
        if (d * e == k * phi + 1) {
			break;
		}
		k++;
	}
	return d;
}

mp::cpp_int decrypt(mp::cpp_int c, mp::cpp_int d, mp::cpp_int n) {
	return mp::powm(c, d, n);
}

mp::cpp_int encrypt(mp::cpp_int m, mp::cpp_int e, mp::cpp_int n) {
	return mp::powm(m, e, n);
}

int main() {

    mp::cpp_int c("62324783949134119159408816513334912534343517300880137691662780895409992760262021");
    mp::cpp_int n("1280678415822214057864524798453297819181910621573945477544758171055968245116423923");
    mp::cpp_int e("65537");


    //mp::cpp_bin_float_100 p = fermat_factorization(n);
    //mp::cpp_bin_float_100 q = n / p;

    // numbers found by fermat factorization
    mp::cpp_int p("1899107986527483535344517113948531328331");
    mp::cpp_int q("674357869540600933870145899564746495319033");


    mp::cpp_int phi = totient(p, q);
    mp::cpp_int private_key = calculate_d(e, phi);
    std::cout << "private_key: " << private_key<< std::endl;

    mp::cpp_int m = decrypt(c, private_key, n);
    std::cout << "Decrypted message m: " << m << std::endl;

   
    return 0;
}
