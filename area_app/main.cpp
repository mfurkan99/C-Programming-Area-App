//MUSTAFA FURKAN ÖZTÜRK 200202148

#include <stdio.h>
#include <graphics.h>
#include <curl/curl.h>
#include <math.h>
#include <string.h>


int num1;
int num2;
int num3;

char buffer[1000]; 
size_t data_length = 0; 

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t data_size = size * nmemb;
    if (data_length + data_size < sizeof(buffer)) {
        memcpy(buffer + data_length, ptr, data_size);
        data_length += data_size;
        return data_size;
    } else {
        return 0; 
    }
}


void drawEdges(int x, int y, int mapSize, int borderColor, int Color) {
    setcolor(borderColor);
    rectangle(x, y, x + mapSize, y + mapSize);
    floodfill(x + mapSize / 2, y + mapSize / 2, borderColor);

    setfillstyle(SOLID_FILL, Color);
    floodfill(x + mapSize / 2, y + mapSize / 2, borderColor);
}


void fillSquare(int numPoints, int (*shape)[2], int mapSize, int borderColor, int Color) {
    int minimum_X = INT_MAX;
    int maximum_X = INT_MIN;
    int minimum_Y = INT_MAX;
    int maximum_Y = INT_MIN;

    
    for (int i = 0; i < numPoints; i++) {
        int x = shape[i][0];
        int y = shape[i][1];
        if (x < minimum_X) minimum_X = x;
        if (x > maximum_X) maximum_X = x;
        if (y < minimum_Y) minimum_Y = y;
        if (y > maximum_Y) maximum_Y = y;
    }

    
    for (int y = minimum_Y; y <= maximum_Y; y++) {
        for (int x = minimum_X; x <= maximum_X; x++) {
            int in = 0;
            for (int i = 0, j = numPoints - 1; i < numPoints; j = i++) {
                int x0 = shape[i][0];
                int y0 = shape[i][1];
                int x1 = shape[j][0];
                int y1 = shape[j][1];

                if ((y0 > y) != (y1 > y) &&
                    x < (x1 - x0) * (y - y0) / (y1 - y0) + x0) {
                    in = !in;
                }
            }

            if (in) {
                drawEdges(x * mapSize, y * mapSize, mapSize, borderColor, Color);
            }
        }
    }
}



//**GERÇEK-ALAN**//
double calculateArea(int num_points, int (*shape)[2]) {
    double alan = 0.0;

    for (int i = 0; i < num_points; i++) {
        int x1 = shape[i][0];
        int y1 = shape[i][1];
        int x2 = shape[(i + 1) % num_points][0];
        int y2 = shape[(i + 1) % num_points][1];

        alan += (x1 * y2 - x2 * y1);
    }

    alan = fabs(alan) / 2.0;

    return alan;
}





int main() {
	CURL *curl;
    CURLcode res;

    const char *url = "http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt"; 

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
    		printf("OKUNAN URL:\n");
    
    		printf("%s", buffer);
    		printf("\n");
} 		else {
    		fprintf(stderr, "HATA! URL Okuma Hatasi: %s\n ", curl_easy_strerror(res));
}

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "CURL Baslatma Hatasi!!!\n");
    }
    
    int choice;

    printf("Hangi satiri goruntulemek istiyorsunuz (1-20) ?\n");
    printf("Satir no: ");
    scanf("%d", &choice);
    
    if (choice < 1 || choice > 20) {
    printf("Hatali giris. Lutfen 1 ile 20 arasinda bir satir numarasi girin.\n");
    return 1; 
}
	
	
	char selectedRow[1000];
    char *ptr = buffer;
    
    int current_Line = 1;
    
    int shapeCount = 1;
	int j=0;
	bool control = false;
	
    
	while (*ptr) {
    if (current_Line == choice) {
        while (*ptr != '(') {
            ptr++;
        }
        printf("");
        int i = 0;
        while (*ptr != 'F') {
            selectedRow[i++] = *ptr; 
            ptr++;
        }
        selectedRow[i] = '\0'; 
        printf("\n");
        break; 
    } else {
        while (*ptr != '\n' && *ptr != '\0') {
            ptr++;
        }
        if (*ptr == '\n') {
            ptr++;
        }
        current_Line++; 
    }
}
  
    
    printf("Satir:%s\n", selectedRow);
    int row_count = 0;
    for (int i = 0; selectedRow[i] != '\0'; i++) {
        if (selectedRow[i] == '(')
            row_count++;
    }

    
    int (*points)[2] = (int(*)[2])malloc(sizeof(int[2]) * row_count);

    
    int current_row = 0;
    for (int i = 0; selectedRow[i] != '\0'; i++) {
        if (selectedRow[i] == '(') {
            int x, y;
            if (sscanf(selectedRow + i, "(%d,%d)", &x, &y) == 2) {
                points[current_row][0] = x;
                points[current_row][1] = y;
                current_row++;
            }
        }
    }
    int shape1[row_count][2];
	int shape2[row_count][2];
	int shape3[row_count][2];
    printf("\nShape %d: ", shapeCount);
    
    for (int i = 0; i < row_count; i++) {
        printf("(%d,%d)", points[i][0], points[i][1]);
        if (points[i][0] == points[j][0] && points[i][1] == points[j][1] && i > 0 && control==true) {
        	 	
            printf("\n");
            printf("\nShape%d eleman sayisi: %d\n", shapeCount, i - j + 1);
            
            if (shapeCount == 1){
    			int a = i-j+1;
    			num1=a;
    			for (int i = 0; i < a; i++) {
    				shape1[i][0] = points[i][0];
    				shape1[i][1] = points[i][1];
				    //printf("%d 1.ÞEKÝLLL %d\n",shape1[i][0],shape1[i][1]);
				    
				}			
			}
			else if (shapeCount == 2){
				int b = i-j+1;
				num2=b;
				for (int i = 0; i < b; i++) {
    				shape2[i][0] = points[i+num1][0];
    				shape2[i][1] = points[i+num1][1];
				    //printf("\n%d 2.ÞEKÝLLL %d\n",shape2[i][0],shape2[i][1]);
				    
				}
			}
			else if (shapeCount == 3){
				int c = i-j+1;
				num3=c;
				for (int i = 0; i < c; i++) {
    				shape3[i][0] = points[i+num1+num2][0];
    				shape3[i][1] = points[i+num1+num2][1];
				    //printf("\n%d 3.ÞEKÝLLL XD %d\n",shape3[i][0],shape3[i][1]);
				    
				}
			}
            
            shapeCount++;
            j = i+1;
			
            if (i < row_count - 1) {
                printf("\nShape %d: \n", shapeCount);
            }
            control=false;
        } else {
            if (i < row_count - 1) {
                printf(",");
                control=true;
            }
        }
    }
    
    

   
    for (int i = 0; i < row_count; i++) {
        //printf("T(%d, %d)\n", points[i][0], points[i][1]);
    }

    
    
    int shape1_area = (int)calculateArea(num1, shape1);
    printf("\nShape1 Yuzey Alani: %d\n", shape1_area);

    
    int shape2_area = (int)calculateArea(num2, shape2);
    printf("Shape2 Yuzey Alani: %d\n", shape2_area);

    
    int shape3_area = (int)calculateArea(num3, shape3);
    printf("Shape3 Yuzey Alani: %d\n", shape3_area);

    
    int toplamAlan = shape1_area + shape2_area + shape3_area;

    
    int rezerv = 10 * toplamAlan;

    printf("Toplam Yuzey Alani: %d\n", toplamAlan);
    printf("Rezerv Degeri: %d\n", rezerv);
    
    int birim_sondaj;
    
    printf("Birim sondaj maliyetini giriniz (1-10) ?\n");
    printf("Birim Sondaj Maliyeti : ");
    scanf("%d", &birim_sondaj);
    
    if (birim_sondaj < 1 || birim_sondaj > 10) {
    printf("Hatali giris. Lutfen 1 ile 10 arasinda bir sondaj maliyeti girin.\n");
    return 1; 
}
	
	int sondaj_maliyeti = toplamAlan * birim_sondaj;
	
	printf("Toplam sondaj maliyeti: %d\n",sondaj_maliyeti);
	
	int birim_platform;
	
	printf("Birim platform maliyetini giriniz ?\n");
	printf("Birim Platform Maliyeti : ");
	scanf("%d",&birim_platform);
	
	int total_square_count=0;
    
    
    initwindow(1024,768);

    int width = 1024;  
    int height = 768; 
    int mapSize = 10; 

    
    setbkcolor(WHITE);
    cleardevice();

    setcolor(LIGHTGRAY); 
    setlinestyle(SOLID_LINE, 0, 2); 

    for (int y = 0; y < height; y += mapSize) {
        for (int x = 0; x < width; x += mapSize) {
            
            rectangle(x, y, x + mapSize, y + mapSize);
        }
    }

    
    setcolor(BLACK); 

    
	
	
    for (int i = 0; i < num1; i++) {
        line(shape1[i][0] * mapSize, shape1[i][1] * mapSize, shape1[(i + 1) % num1][0] * mapSize, shape1[(i + 1) % num1][1] * mapSize);
    }

    
    for (int i = 0; i < num2; i++) {
        line(shape2[i][0] * mapSize, shape2[i][1] * mapSize, shape2[(i + 1) % num2][0] * mapSize, shape2[(i + 1) % num2][1] * mapSize);
    }

    
    for (int i = 0; i < num3; i++) {
        line(shape3[i][0] * mapSize, shape3[i][1] * mapSize, shape3[(i + 1) % num3][0] * mapSize, shape3[(i + 1) % num3][1] * mapSize);
    }
    
    
	fillSquare(num1, shape1, mapSize, BLACK, RED);
	fillSquare(num2, shape2, mapSize, BLACK, BLUE);
	fillSquare(num3, shape3, mapSize, BLACK, GREEN);
    

    
    settextstyle(SMALL_FONT, HORIZ_DIR, 4); 

    for (int i = 0; i < row_count; i++) {
        char coordString[20];
        sprintf(coordString, "(%d,%d)", points[i][0], points[i][1]);
        
        outtextxy(points[i][0] * mapSize+5, points[i][1] * mapSize - 5, coordString);
    }
    

    delay(5000000);
	
    closegraph();
    free(points);
    return 0;
}
