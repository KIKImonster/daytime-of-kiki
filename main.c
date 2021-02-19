nt main()
{

    printf("测试代码\n");
    BiTree T;
    T = (BiTree)malloc(sizeof(BiTreeNode));

    printf("请给二叉树按照先序方式依次输入结点的值(空结点为#):\n");
    CreateBiTree(&T);


    printf("先序方式遍历结果：\n");
    PreOrderTravel(T);
    printf("\n");

    printf("中序方式遍历结果：\n");
    InOrderTravel(T);
    printf("\n");


    return 0;
}

