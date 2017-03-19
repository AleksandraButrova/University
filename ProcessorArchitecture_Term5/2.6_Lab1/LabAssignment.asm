; ------------------------------------------------------------------------------------;
;	Лабораторная работа №2 по курсу Программирование на языке ассемблера				;
;	Вариант №2.6.																		;
;	Выполнил студент Бутрова Александра.												;
;																						;
;	Исходный модуль LabAssignment.asm													;
;	Содержит функцию на языке ассемблера, разработанную в соответствии с заданием		;
; ------------------------------------------------------------------------------------;
;	Задание:																			;
;		Реализовать фильтр Собеля обработки изображений									;

.DATA
vec1210		real4	1., 2., 1., 0.						; Вектор домножения для xmm3 
vec2222		real4	2., 2., 2., 2.						; Вектор домножения для xmm1
over		real4	255., 255., 255., 255.

.CODE
; ----------------------------------------------------------------------------------;
; Осуществляет фильтрацию одной цветовой составляющей изображения					  ;
; void Kernel_asm( PBYTE pDst, PBYTE pSrc, int Width )								  ;
; Параметры:																		  ;
;	pDst   - адрес пиксела - результата обработки									  ;
;   pSrc   - адрес пиксела исходного изображения									  ;
;	Width  - ширина изображения в пикселах (количество столбцов)					  ;
; Внимание!!! Для корректной работы приложения необходимо определить константы в файле;
;	Tuning.h в соответствии с заданием												  ;
; ----------------------------------------------------------------------------------;


; Будем рассматривать матрицу 3 х 3, где обрабатывать будем центральный пиксель z5

;	( z1  z2  z3 )	
;	( z4  z5  z6 )
;	( z7  z8  z9 ) 

; Вычислить z5 можно по формуле
; z5 = sqrt ( Gx*Gx + Gy*Gy )
; где Gx и Gy
; Gy = ( z8 - z2 ) * 2 + z7 + z9 - z1 - z3
; Gx = ( z6 - z4 ) * 2 + z3 + z9 - z1 - z7


Kernel PROC											; [RCX] - pDst
													; [RDX] - pSrc
													; R8    - Width

	
	sub			rsp, 32*8
	vmovdqu		ymmword ptr[ rsp + 32*0 ], ymm6		; Сохраним все регистры
	vmovdqu		ymmword ptr[ rsp + 32*1 ], ymm7		
	vmovdqu		ymmword ptr[ rsp + 32*2 ], ymm8
	vmovdqu		ymmword ptr[ rsp + 32*3 ], ymm9
	vmovdqu		ymmword ptr[ rsp + 32*4 ], ymm10
	vmovdqu		ymmword ptr[ rsp + 32*5 ], ymm11
	vmovdqu		ymmword ptr[ rsp + 32*6 ], ymm12
	vmovdqu		ymmword ptr[ rsp + 32*7 ], ymm13
	
	vzeroall										; Обнулим все регистры
	
	vpmovzxbd	xmm0, dword ptr[ rdx ]
	vcvtdq2ps	xmm0, xmm0							; xmm0 = ( z1, z2, z3, * )

	vpmovzxbd	xmm1, dword ptr[ rdx + R8 ]
	vcvtdq2ps	xmm1, xmm1							; xmm1 = ( z4, z5, z6, * )

	vpmovzxbd	xmm2, dword ptr[ rdx + 2 * R8 ]
	vcvtdq2ps	xmm2, xmm2							; xmm2 = ( z7, z8, z9, * )



; Будем считать Gy
; Перепишем так Gy = ( z8  - z2 ) * 2 + ( z7 - z1 ) + ( z9 - z3 )
; Все слагаемые имеются в следующем регистре xmm3

	vsubps		xmm3, xmm2, xmm0					; xmm3 = ( z7 - z1 , z8 - z2 , z9 - z3, * )
													; Осталось сложить и возвести в квадрат
													; Домножим на вектор ( 1, 2, 1, 0 ), чтобы всё ок для формулы было
	vmulps		xmm3, xmm3, xmmword ptr [vec1210]	; xmm3 = ( z7 - z1 , ( z8 - z2 ) * 2 , z9 - z3, 0 )
													; Нехитрое сложение. Повторим 2 раза.
	vhaddps		xmm3, xmm3, xmm3					; xmm3 = ( z7 - z1 + ( z8 - z2 ) * 2 , z9 - z3) x2 раза
	vhaddps		xmm3, xmm3, xmm3					; xmm3 = ( z7 - z1 + ( z8 - z2 ) * 2 +  z9 - z3) х4 раза
													; Т.е. xmm3 = ( Gy, Gy, Gy, Gy )
	vmulps		xmm3, xmm3, xmm3					; xmm3 = ( Gy^2, Gy^2, Gy^2, Gy^2 )



; Теперь займёмся Gy
; Перепишем Gx = ( z6 - z4 ) * 2 + ( z3 - z1 ) + ( z9 - z7 )
; ! Будем изменять xmm0, xmm1, xmm2 так как в нашем случае они больше не для чего не нужны
; Тут будем менять местами столбцы по маске 11 01 11 01, так как средний столбец из z2, z5, z8 нам мешает
; А потом просто всё поскладываем и повычитаем 

	vshufps		xmm0, xmm0, xmm0, 11011101b			; xmm0 = ( z1, z3, z1, z3 )
	vshufps		xmm1, xmm1, xmm1, 11011101b			; xmm1 = ( z4, z6, z4, z6 )
	vshufps		xmm2, xmm2, xmm2, 11011101b			; xmm2 = ( z7, z9, z7, z9 )
													; Вычитаем внутри регистов
	vhsubps		xmm0, xmm0, xmm0					; xmm0 = ( z3 - z1 ) х4 раза
	vhsubps		xmm1, xmm1, xmm1					; xmm1 = ( z6 - z4 ) x4 раза
	vhsubps		xmm2, xmm2, xmm2					; xmm2 = ( z9 - z7 ) x4 раза
													; Перед сложением надо xmm1 приведем к нужному виду
	vmulps		xmm1, xmm1, xmmword ptr [vec2222]	; xmm1 = ( ( z6-z4 ) * 2 ) х4 раза
													; Время сложения!
	vaddps		xmm0, xmm0, xmm1					; xmm0 = ( ( ( z6 - z4 ) * 2 ) +  ( z3 - z1 ) ) х4 раза 
	vaddps		xmm0, xmm0, xmm2					; xmm0 = ( ( ( z6 - z4 ) * 2 ) +  ( z3 - z1 ) + ( z9 - z7 ) ) х4 раза 
													; Т.е. xmm0 = ( Gx, Gx, Gx, Gx )
	vmulps		xmm0, xmm0, xmm0					; xmm3 = ( Gx^2, Gx^2, Gx^2, Gx^2 )



; Всё отлично. 
; Осталось сложить xmm0 и xmm3
; Затем извлечь корень
; И записать по адресу rcx

	vaddps		xmm0, xmm0, xmm3					; xmm0 = ( Gx^2 + Gy^2 ) x4 раза
	vsqrtps		xmm0, xmm0							; xmm0 = ( sqrt ( Gx^2 + Gy^2 ) ) x4 раза
													; Проверим на переполнение
	vbroadcastss xmm4, over							; xmm4 = ( 255, 255, 255, 255 )
	vminps		xmm0, xmm0, xmm4					; В минус уйти не можем. С помощью выбора минимума обеспечиваем не выход за пределы 
	vcvtps2dq	xmm0, xmm0							; Конвертируем в целые
	vpextrb		byte ptr [rcx], xmm0, 0				; Положим первый байт xmm0 по адресу элемента z5
	
	
	vmovdqu		ymm6, ymmword ptr[rsp + 32*0]		; Восстановим регистры
	vmovdqu		ymm7, ymmword ptr[rsp + 32*1]
	vmovdqu		ymm8, ymmword ptr[rsp + 32*2]
	vmovdqu		ymm9, ymmword ptr[rsp + 32*3]
	vmovdqu		ymm10, ymmword ptr[rsp + 32*4]
	vmovdqu		ymm11, ymmword ptr[rsp + 32*5]
	vmovdqu		ymm12, ymmword ptr[rsp + 32*6]
	vmovdqu		ymm13, ymmword ptr[rsp + 32*7]
	add			rsp, 32*8

	vzeroall										; Обнулим регистры за собой
	ret												; И вернёмся обратно
Kernel ENDP
END													; Конец :)
