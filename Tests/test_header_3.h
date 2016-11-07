//Testcase for the padding at the end of a struct and for the correct behavaior of the input alignment option.

struct Test 
{
    int a;
    int b;
    int c;
    struct in{
        int ab;
        double bc;
    } inner;
    int d;
};

struct AlignTest 
{
    char a;
    char b[5];
    char c;
    int d;
    char e;
};

//----------------------------------
//Memory alignment option = 8 bytes:
//Size 48
//Padding 20
// struct Test 
// {
//     int a;//4
//     //4
//     int b;//4
//     //4
//     int c;//4
//     //4
//     struct in{
//         int ab;//4
//         //4
//         double bc;//8
//     } inner;
//     int d;//4
//     //4
// };
//
//
//Size 40
//Padding 28
// struct AlignTest 
// {
//     char a;//1
//     //7
//     char b[5];//5
//     //3
//     char c;//1
//     //7
//     int d;//4
//     //4
//     char e;//1
//     //7
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 40
//Padding 12
// struct Test 
// {
//     int a;//4
//     int b;//4
//     int c;//4
//     //4
//     struct in{
//         int ab;//4
//         //4
//         double bc;//8
//     } inner;
//     int d;//4
//     //4
// };
//
//
//Size 24
//Padding 12
// struct AlignTest 
// {
//     char a;//1
//     //3
//     char b[5];//5
//     //3
//     char c;//1
//     //3
//     int d;//4
//     char e;//1
//     //3
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 40
//Padding 12
// struct Test 
// {
//     int a;//4
//     int b;//4
//     int c;//4
//     //4
//     struct in{
//         int ab;//4
//         //4
//         double bc;//8
//     } inner;
//     int d;//4
//     //4
// };
//
//
//Size 20
//Padding 8
// struct AlignTest 
// {
//     char a;//1
//     //1
//     char b[5];//5
//     //1
//     char c;//1
//     //3
//     int d;//4
//     char e;//1
//     //3
// };
//----------------------------------