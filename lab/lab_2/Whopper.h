//
//  Whopper.h
//  test
//
//  Created by John Stuart on 10/9/15.
//  Copyright © 2015 John Stuart. All rights reserved.
//

#ifndef Whopper_h
#define Whopper_h

#include <cmath>

using namespace std;

void reverse(vector<int> &);
vector<int> toChunks(int);
vector<int> toChunks2(int);
int toInt(vector<int> &);
vector<int> isBigger(vector<int> &, vector<int> &);
vector<int> addChunks(vector<int> &, vector<int> &);
vector<int> subChunks(vector<int> &, vector<int> &);
vector<int> multChunks(vector<int> &, vector<int> &);

class whopper {
public:
        int sign;
        vector<int> chunks;
    public:
        whopper() {
            sign = 0;
        }
        whopper(int num) {
            //store the sign, change the sign, eliminate the sign, store the vector
            if (num < 0) {
                sign = -1;
                chunks = toChunks(num);
            }
            //store the sign, eliminate the sign, store the vector
            else if (num > 0) {
                sign = 1;
                chunks = toChunks(num);
            }
            else if (num == 0) {
                sign = 0;
            }
            else cout << "ERROR" << endl;
        }
        void print() {
            cout << sign;
            for (int i = 0; i < chunks.size(); i++) {
                cout << chunks[i];
            }
            cout << endl;
        }
        whopper operator + (whopper w) {
            whopper result;
            if (this->sign < 0 && w.sign < 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = -1;
                    result.chunks = addChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = -1;
                    result.chunks = addChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign > 0 && w.sign > 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = 1;
                    result.chunks = addChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = 1;
                    result.chunks = addChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign < 0 && w.sign > 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = -1;
                    result.chunks = subChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = 1;
                    result.chunks = subChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign > 0 && w.sign < 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = 1;
                    result.chunks = subChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = -1;
                    result.chunks = subChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign == 0 && w.sign < 0) {
                result.sign = -1;
                result.chunks = w.chunks;
            }
            else if (this->sign == 0 && w.sign > 0) {
                result.sign = 1;
                result.chunks = w.chunks;
            }
            else if (this->sign == 0 && w.sign == 0) {
                result.sign = 0;
            }
            else if (this->sign < 0 && w.sign == 0) {
                result.sign = -1;
                result.chunks = this->chunks;
            }
            else if (this->sign > 0 && w.sign == 0) {
                result.sign = 1;
                result.chunks = this->chunks;
            }
            
            return result;
        }
        whopper operator - (whopper w) {
            whopper result;
            if (this->sign < 0 && w.sign < 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = -1;
                    result.chunks = subChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = 1;
                    result.chunks = subChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign > 0 && w.sign > 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = 1;
                    result.chunks = subChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = -1;
                    result.chunks = subChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign < 0 && w.sign > 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = -1;
                    result.chunks = addChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = -1;
                    result.chunks = addChunks(w.chunks, this->chunks);
                }
                
            }
            else if (this->sign > 0 && w.sign < 0) {
                if (isBigger(this->chunks, w.chunks) == this->chunks) {
                    result.sign = 1;
                    result.chunks = addChunks(this->chunks, w.chunks);
                }
                else {
                    result.sign = 1;
                    result.chunks = addChunks(w.chunks, this->chunks);
                }
            }
            else if (this->sign == 0 && w.sign < 0) {
                result.sign = 1;
                result.chunks = w.chunks;
            }
            else if (this->sign == 0 && w.sign > 0) {
                result.sign = -1;
                result.chunks = w.chunks;
            }
            else if (this->sign == 0 && w.sign == 0) {
                result.sign = 0;
            }
            else if (this->sign < 0 && w.sign == 0) {
                result.sign = -1;
                result.chunks = this->chunks;
            }
            else if (this->sign > 0 && w.sign == 0) {
                result.sign = 1;
                result.chunks = this->chunks;
            }
            return result;
        }
        bool operator > (whopper w) {
            if (this->sign > 0 && w.sign < 0) {
                cout << "true" << endl;
                return true;
            }
            else if (this->sign < 0 && w.sign > 0) {
                cout << "false" << endl;
                return false;
            }
            else if (this->sign == 0 && w.sign > 0) {
                cout << "false" << endl;
                return false;
            }
            else if (this->sign == 0 && w.sign < 0) {
                cout << "true" << endl;
                return true;
            }
            else if (this->sign > 0 && w.sign == 0) {
                cout << "true" << endl;
                return true;
            }
            else if (this->sign < 0 && w.sign == 0) {
                cout << "false" << endl;
                return false;
            }
            else {
                if (this-> sign == -1 && isBigger(this->chunks, w.chunks) == this->chunks) {
                    cout << "false" << endl;
                    return true;
                }
                else if (this-> sign == 1 && isBigger(this->chunks, w.chunks) == this->chunks) {
                    cout << "true" << endl;
                    return true;
                }
                else cout << "false" << endl; return false;
            }
        }
        whopper operator * (whopper w) {
            whopper result;
            if (this->sign == w.sign) {
                result.sign = 1;
                result.chunks = multChunks(this->chunks, w.chunks);
            }
            else if (this->sign != w.sign && this->sign != 0 && w.sign != 0) {
                result.sign = -1;
                result.chunks = multChunks(this->chunks, w.chunks);
            }
            else if (this->sign == 0 || w.sign == 0) {
                result.sign = 0;
            }
            return result;
        }
    
};

vector<int> toChunks(int num) {
    vector<int> chunks;
    int power;
    num = abs(num);
    int temp = num;
    int length = 1;
    while (temp /= 10 ) {
        length++;
    }
    power = pow(10, length - 1);
    num %= power;
    
    do {
        chunks.push_back(num % 100);
    } while (num /= 100);
    
    if (chunks.size() > 1) {
        reverse(chunks);
    }
    
    return chunks;
    
}

vector<int> toChunks2(int num, int hundreds) {
    vector<int> c;
    do {
        c.push_back(num % 100);
    } while (num /= 100);
    
    if (c.size() > 1) {
        reverse(c);
    }
    if (hundreds != 0) {
        for(int i = 0; i < hundreds; i++) {
            c.push_back(00);
        }
    }
    return c;
}

int toInt(vector<int> &chunk) {
    int integer = 0;
    for (int i = 0; i < chunk.size(); i++) {
        integer *= 100;
        integer += chunk[i];
    }
    return integer;
}

vector<int> isBigger (vector<int> &a, vector<int> &b) {
    if (a.size() > b.size()) {
        return a;
    }
    else if (a.size() < b.size()) {
        return b;
    }
    else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] > b[i]) {
                return a;
            }
            else if (a[i] < b[i]) {
                return b;
            }
        }
    }
    return a;
}

vector<int> addChunks(vector<int> &a, vector<int> &b) {
    vector<int> c (0,0);
    int carry = 0;
    int j = 0;
    for (int i = (a.size() - 1); i >= 0; i--) {
        if (j < b.size()) {
            if (carry == 0) {
                if (a[i] + b[b.size() - 1 - j] >= 100) {
                    c.push_back(a[i] + b[b.size() - 1 - j] - 100);
                    carry++;
                }
                else {
                    c.push_back(a[i] + b[b.size() - 1 - j]);
                }
            }
            else {
                if (a[i] + b[b.size() - 1 - j] + carry >= 100) {
                    c.push_back(a[i] + b[b.size() - 1 - j] + carry - 100);
                }
                else {
                    c.push_back(a[i] + b[b.size() - 1 - j] + carry);
                    carry--;
                }
            }
        }
        else if (j >= b.size()) {
            if (carry == 0) {
                c.push_back(a[i]);
            }
            else {
                if (a[i]+ carry >= 100) {
                    c.push_back(a[i] + carry - 100);
                }
                else {
                    c.push_back(a[i] + carry);
                    carry--;
                }
            }
        }
        j++;
        
    }
    if (carry == 1) {
        int temp;
        temp = c.back() - 100;
        c.pop_back();
        c.push_back(temp);
        c.push_back(1);
    }
    
    reverse(c);
    return c;
}

vector<int> subChunks(vector<int> &a, vector<int> &b) {
    vector<int> c (0,0);
    int carry = 0;
    int j = 0;
    for (int i = (a.size() - 1); i >= 0; i--) {
        if (j < b.size()) {
            if (carry == 0) {
                if (a[i] - b[b.size() - 1 - j] < 0) {
                    c.push_back(a[i] - b[b.size() - 1 - j] + 100);
                    carry++;
                }
                else {
                    c.push_back(a[i] - b[b.size() - 1 - j]);
                }
            }
            else {
                if (a[i] - b[b.size() - 1 - j] - carry < 0) {
                    c.push_back(a[i] - b[b.size() - 1 - j] - carry + 100);
                }
                else {
                    c.push_back(a[i] - b[b.size() - 1 - j] - carry);
                    carry--;
                }
            }
        }
        else if (j >= b.size()) {
            if (carry == 0) {
                c.push_back(a[i]);
            }
            else {
                if (a[i] - carry < 0) {
                    c.push_back(a[i] - carry + 100);
                }
                else {
                    c.push_back(a[i] - carry);
                    carry--;
                }
            }
        }
        j++;
    }
    
    reverse(c);
    return c;
}

vector<int> multChunks(vector<int> &a, vector<int> &b) {
    vector<int> c;
    vector<int> products;
    int finalProduct = 0;
    int hundreds = 1;
    int hundreds2 = 0;
    int integer = toInt(a);
    vector< vector<int> > prodToChunk;
    
    
    /*for (int i = (b.size() - 1); i >= 0; i--) {
        products.push_back(integer * b[i] * hundreds);
        hundreds *= 100;
    }
    
    for (int i = 0; i < products.size(); i++) {
        finalProduct += products[i];
    }
    
    do {
        c.push_back(finalProduct % 100);
    } while (finalProduct /= 100);
    
    if (c.size() > 1) {
        reverse(c);
    }*/
    for (int i = (b.size() - 1); i >= 0; i--) {
        products.push_back(integer * b[i]);
        prodToChunk.push_back(toChunks2(products.back(), hundreds2));
        hundreds2++;
    }
    
    for (int i = (prodToChunk.size() - 2); i >= 0; i--) {
        
        prodToChunk.back() = addChunks(prodToChunk.back(), prodToChunk[i]);
    }
    c = prodToChunk.back();
    return c;
}

void reverse(vector<int> &chunks) {
    
    if (chunks.size() % 2 == 0) {
        for (int i = 0, j = chunks.size() - 1; i <= (chunks.size() / 2) - 1; i++, j--) {
            int temp = chunks[i];
            chunks[i] = chunks[j];
            chunks[j] = temp;
        }
    }
    else if (chunks.size() % 2 != 0) {
        for (int i = 0, j = chunks.size() - 1; i <= ((chunks.size() - 1) / 2) - 1; i++, j--) {
            int temp = chunks[i];
            chunks[i] = chunks[j];
            chunks[j] = temp;
        }
    }
    
}

        

#endif /* Whopper_h */
