#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
使用者可以選擇1.新增商品2.刪除商品，若選擇1則可依序輸入商品名稱、商品單價和商品數量，然後計算總價，
購物車中最多只能有20項商品(每一個元素內含一件商品的資料結構)。
當選擇1.新增商品時依序輸入商品名稱、商品價格和商品數量，如果購買同一項商品數量超過≥3 件，商品價格打 8 折。
若選擇2則可根據商品索引刪除購物車中的商品。
*/
struct item {
    char name[20];     // 商品名稱
    int price;         // 商品單價
    int quantity;      // 商品數量
    int final_price;
}; // 最終單價	
//也可void calculate_price(struct item* p_items);
int calculate_price(struct item* p_items);
void print_cart(struct item* p_items, int count);
int main() {
    int choose = 0;
    int count = 0;
    struct item cart[20];//購物車有20項
    printf("----------歡迎來到購物車清單----------\n");
    printf("(若購買同項商品數量超過3件，商品價格打8折)\n");
    while (choose != -1) {
        printf("請選擇：1.新增商品 2.刪除商品 (-1結束): ");
        scanf("%d", &choose);
        switch (choose) {//記得大括號
        case 1:
            if (count >= 20) {
                printf("購物車已滿，無法新增商品。\n");
                break;
            }
            printf("第%d件商品名稱:", count + 1);
            //陣列第1項cart[count=0] 因為要顯示數字:第"0+1"項
            scanf("%s", cart[count].name);//字串%s，存取後面不用&

            printf("第%d件商品單價", count + 1);
            scanf("%d", &(cart[count].price));

            printf("第%d件商品數量", count + 1);
            scanf("%d", &(cart[count].quantity));

            cart[count].final_price = calculate_price(&cart[count]);
            //calculate_price(&cart[count]);//算最終價
            count++;//記數 從cart[0.1.2...]往下遞增

            print_cart(cart, count);//印購物車清單
            break;//記得!
        case 2:
            if (count == 0) {
                printf("購物車中無商品可刪除。\n");
                break;
            }
            int delete_index;//case2的刪除用參數
            printf("請輸入要刪除的商品索引：");
            scanf("%d", &delete_index);
            if (delete_index < 1 || delete_index > count) {
                printf("無效的索引，請重新輸入。\n");
                break;
            }
            // 將後面的商品往前替補
            //起點:因刪除的商品的索引從No.1開始的，而陣列索引是從0開始的，所以要減1。
            //過程:當前的索引i不能超過購物車商品總數減1，因為最後的商品不需再向前移動。
            for (int i = delete_index - 1; i < count - 1; i++) {
                cart[i] = cart[i + 1];//後者向前覆蓋
            }
            count--;//往前遞減

            print_cart(cart, count);//印購物車清單
            break;//記得!

        case -1:
            printf("程式結束。\n");
            break;
        default:
            printf("無效的選擇，請重新輸入。\n");
            break;
        }
    }
    return 0;
}
//void calculate_price(struct item* p_item){
int calculate_price(struct item* p_items) {
    int value = 0;
    if (p_items->quantity >= 3) {//數量超過 ? 3 件，商品價格打8 折
        p_items->final_price = p_items->price * p_items->quantity * 0.8;
    }
    else {
        p_items->final_price = p_items->price * p_items->quantity;
    }
    value = (p_items)->final_price; return value;
}
void print_cart(struct item* p_items, int count) {
    //注意p_items是struct item的指標
    printf("-------------------------------------------------\n");
    printf("商品索引\t商品名稱\t商品單價\t商品數量\t最終價格\n");
    int total_price = 0;
    for (int i = 0; i < count; i++) {//i是第0個陣列也就是第一項
        printf("No%d\t\t", i + 1);//第0+1項
        printf("%s\t\t", p_items[i].name);//同理(p_items+i)->name
        printf("%d\t\t", p_items[i].price);//同理(p_items+i)->price
        printf("%d\t\t", p_items[i].quantity);
        printf("%d\n", p_items[i].final_price);

        total_price += p_items[i].final_price;
        //(p_items + i)->final_price
    }
    printf("總價為：%d\n\n", total_price);
}

