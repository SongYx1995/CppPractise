
void func(int& a) {

}
int main() {
    int b;
    int& a = b;
    int& c = a;
    func(a);
}