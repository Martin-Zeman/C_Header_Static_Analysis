//Testcase with no padding using arrays.

struct A2
{
    char m1[8];
    double m2[2];
    int m3[2];
};

//----------------------------------
//Memory alignment option = 8 bytes:
//Size 32
//Padding 0
// struct A2
// {
//     char m1[8];//8
//     double m2[2];//16
//     int m3[2];//8
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 32
//Padding 0
// struct A2
// {
//     char m1[8];//8
//     double m2[2];//16
//     int m3[2];//8
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 32
//Padding 0
// struct A2
// {
//     char m1[8];//8
//     double m2[2];//16
//     int m3[2];//8
// };
//----------------------------------
