//Testcase of an array of a nested sctruct as well as an array of a nested struct with a previous definition. This testcase is alignment option invariant.

struct A1
{
    char m1[3];
    double m2;
    char m3;
    struct Nested
    {
        char m1;
        double m2;
    } m4[2];
    struct Nested m5[2];
    struct Nested m6;
};

//----------------------------------
//Memory alignment option = 8 bytes:
//Size 104
//Padding 47 
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
//     } m4[2];//size 32, padding 14
//     struct Nested m5[2];//size 32, padding 14
//     struct Nested m6;//size 16, padding 7
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 104
//Padding 47
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
//     } m4[2];//size 32, padding 14
//     struct Nested m5[2];//size 32, padding 14
//     struct Nested m6;//size 16, padding 7
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 104
//Padding 47
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
//     } m4[2];//size 32, padding 14
//     struct Nested m5[2];//size 32, padding 14
//     struct Nested m6;//size 16, padding 7
// };
//----------------------------------