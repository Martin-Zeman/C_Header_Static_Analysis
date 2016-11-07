//Testcase for using previously declared structs including nested structs. This testcase is alignment option invariant.

struct A1
{
    char m1[3];
    double m2;
    char m3;
    struct Nested
    {
        char m1;
        double m2;
    } m4;
};

struct A2
{
    char m1;
    double m2;
    struct Nested m5;
    char m3;
};

struct A3
{
    struct A1 S1;
    struct A2 S2;
};

//----------------------------------
//Memory alignment option = 8 bytes:
//Size 40
//Padding 19
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
//     struct Nested
//     {
//         char m1;//1
//         //7
//         double m2;//8
//     } m4;
// };
// 
//Size 40
//Padding 21
// struct A2
// {
//     char m1;//1
//     //7
//     double m2;//8
//     struct Nested m5;//Size 16, Padding 7
//     char m3;//1
//     //7
// };
// 
//Size 80
//Padding 40
// struct A3
// {
//     struct A1 S1;//Size 40, Padding 19
//     struct A2 S2;//Size 40, Padding 21
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 40
//Padding 19
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
//     struct Nested
//     {
//         char m1;//1
//         //7
//         double m2;//8
//     } m4;
// };
// 
//Size 40
//Padding 21
// struct A2
// {
//     char m1;//1
//     //7
//     double m2;//8
//     struct Nested m5;//Size 16, Padding 7
//     char m3;//1
//     //7
// };
// 
//Size 80
//Padding 40
// struct A3
// {
//     struct A1 S1;//Size 40, Padding 19
//     struct A2 S2;//Size 40, Padding 21
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 40
//Padding 19
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
//     struct Nested
//     {
//         char m1;//1
//         //7
//         double m2;//8
//     } m4;
// };
// 
//Size 40
//Padding 21
// struct A2
// {
//     char m1;//1
//     //7
//     double m2;//8
//     struct Nested m5;//Size 16, Padding 7
//     char m3;//1
//     //7
// };
// 
//Size 80
//Padding 40
// struct A3
// {
//     struct A1 S1;//Size 40, Padding 19
//     struct A2 S2;//Size 40, Padding 21
// };
//----------------------------------