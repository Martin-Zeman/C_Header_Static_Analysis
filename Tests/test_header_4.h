//Testcase for the alignment of inner structs.

struct A1
{
    char m1[3];
    int m2;
    char m3;
    double m4;
    char m5;
    struct Nested
    {
        char n1;
        double n2;
    } low;
};


//----------------------------------
//Memory alignment option = 8 bytes:
//Size 56
//Padding 30 
// struct A1
// {
//     char m1[3];//3
//     //5
//     int m2;//4
//     //4
//     char m3;//1
//     //7
//     double m4;//8
//     char m5;//1
//     //7
//     struct Nested
//     {
//         char n1;//1
//         //7
//         double n2;//8
//     } low;
//};
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 48
//Padding 22
// struct A1
// {
//     char m1[3];//3
//     //1
//     int m2;//4
//     char m3;//1
//     //7
//     double m4;//8
//     char m5;//1
//     //7
//     struct Nested
//     {
//         char n1;//1
//         //7
//         double n2;//8
//     } low;
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 48
//Padding 22 
// struct A1
// {
//     char m1[3];//3
//     //1
//     int m2;//4
//     char m3;//1
//     //7
//     double m4;//8
//     char m5;//1
//     //7
//     struct Nested
//     {
//         char n1;//1
//         //7
//         double n2;//8
//     } low;
// };
//----------------------------------