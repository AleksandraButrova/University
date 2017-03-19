; ------------------------------------------------------------------------------------;
;	������������ ������ �2 �� ����� ���������������� �� ����� ����������				;
;	������� �2.6.																		;
;	�������� ������� ������� ����������.												;
;																						;
;	�������� ������ LabAssignment.asm													;
;	�������� ������� �� ����� ����������, ������������� � ������������ � ��������		;
; ------------------------------------------------------------------------------------;
;	�������:																			;
;		����������� ������ ������ ��������� �����������									;

.DATA
vec1210		real4	1., 2., 1., 0.						; ������ ���������� ��� xmm3 
vec2222		real4	2., 2., 2., 2.						; ������ ���������� ��� xmm1
over		real4	255., 255., 255., 255.

.CODE
; ----------------------------------------------------------------------------------;
; ������������ ���������� ����� �������� ������������ �����������					  ;
; void Kernel_asm( PBYTE pDst, PBYTE pSrc, int Width )								  ;
; ���������:																		  ;
;	pDst   - ����� ������� - ���������� ���������									  ;
;   pSrc   - ����� ������� ��������� �����������									  ;
;	Width  - ������ ����������� � �������� (���������� ��������)					  ;
; ��������!!! ��� ���������� ������ ���������� ���������� ���������� ��������� � �����;
;	Tuning.h � ������������ � ��������												  ;
; ----------------------------------------------------------------------------------;


; ����� ������������� ������� 3 � 3, ��� ������������ ����� ����������� ������� z5

;	( z1  z2  z3 )	
;	( z4  z5  z6 )
;	( z7  z8  z9 ) 

; ��������� z5 ����� �� �������
; z5 = sqrt ( Gx*Gx + Gy*Gy )
; ��� Gx � Gy
; Gy = ( z8 - z2 ) * 2 + z7 + z9 - z1 - z3
; Gx = ( z6 - z4 ) * 2 + z3 + z9 - z1 - z7


Kernel PROC											; [RCX] - pDst
													; [RDX] - pSrc
													; R8    - Width

	
	sub			rsp, 32*8
	vmovdqu		ymmword ptr[ rsp + 32*0 ], ymm6		; �������� ��� ��������
	vmovdqu		ymmword ptr[ rsp + 32*1 ], ymm7		
	vmovdqu		ymmword ptr[ rsp + 32*2 ], ymm8
	vmovdqu		ymmword ptr[ rsp + 32*3 ], ymm9
	vmovdqu		ymmword ptr[ rsp + 32*4 ], ymm10
	vmovdqu		ymmword ptr[ rsp + 32*5 ], ymm11
	vmovdqu		ymmword ptr[ rsp + 32*6 ], ymm12
	vmovdqu		ymmword ptr[ rsp + 32*7 ], ymm13
	
	vzeroall										; ������� ��� ��������
	
	vpmovzxbd	xmm0, dword ptr[ rdx ]
	vcvtdq2ps	xmm0, xmm0							; xmm0 = ( z1, z2, z3, * )

	vpmovzxbd	xmm1, dword ptr[ rdx + R8 ]
	vcvtdq2ps	xmm1, xmm1							; xmm1 = ( z4, z5, z6, * )

	vpmovzxbd	xmm2, dword ptr[ rdx + 2 * R8 ]
	vcvtdq2ps	xmm2, xmm2							; xmm2 = ( z7, z8, z9, * )



; ����� ������� Gy
; ��������� ��� Gy = ( z8  - z2 ) * 2 + ( z7 - z1 ) + ( z9 - z3 )
; ��� ��������� ������� � ��������� �������� xmm3

	vsubps		xmm3, xmm2, xmm0					; xmm3 = ( z7 - z1 , z8 - z2 , z9 - z3, * )
													; �������� ������� � �������� � �������
													; �������� �� ������ ( 1, 2, 1, 0 ), ����� �� �� ��� ������� ����
	vmulps		xmm3, xmm3, xmmword ptr [vec1210]	; xmm3 = ( z7 - z1 , ( z8 - z2 ) * 2 , z9 - z3, 0 )
													; �������� ��������. �������� 2 ����.
	vhaddps		xmm3, xmm3, xmm3					; xmm3 = ( z7 - z1 + ( z8 - z2 ) * 2 , z9 - z3) x2 ����
	vhaddps		xmm3, xmm3, xmm3					; xmm3 = ( z7 - z1 + ( z8 - z2 ) * 2 +  z9 - z3) �4 ����
													; �.�. xmm3 = ( Gy, Gy, Gy, Gy )
	vmulps		xmm3, xmm3, xmm3					; xmm3 = ( Gy^2, Gy^2, Gy^2, Gy^2 )



; ������ ������� Gy
; ��������� Gx = ( z6 - z4 ) * 2 + ( z3 - z1 ) + ( z9 - z7 )
; ! ����� �������� xmm0, xmm1, xmm2 ��� ��� � ����� ������ ��� ������ �� ��� ���� �� �����
; ��� ����� ������ ������� ������� �� ����� 11 01 11 01, ��� ��� ������� ������� �� z2, z5, z8 ��� ������
; � ����� ������ �� ������������ � ���������� 

	vshufps		xmm0, xmm0, xmm0, 11011101b			; xmm0 = ( z1, z3, z1, z3 )
	vshufps		xmm1, xmm1, xmm1, 11011101b			; xmm1 = ( z4, z6, z4, z6 )
	vshufps		xmm2, xmm2, xmm2, 11011101b			; xmm2 = ( z7, z9, z7, z9 )
													; �������� ������ ��������
	vhsubps		xmm0, xmm0, xmm0					; xmm0 = ( z3 - z1 ) �4 ����
	vhsubps		xmm1, xmm1, xmm1					; xmm1 = ( z6 - z4 ) x4 ����
	vhsubps		xmm2, xmm2, xmm2					; xmm2 = ( z9 - z7 ) x4 ����
													; ����� ��������� ���� xmm1 �������� � ������� ����
	vmulps		xmm1, xmm1, xmmword ptr [vec2222]	; xmm1 = ( ( z6-z4 ) * 2 ) �4 ����
													; ����� ��������!
	vaddps		xmm0, xmm0, xmm1					; xmm0 = ( ( ( z6 - z4 ) * 2 ) +  ( z3 - z1 ) ) �4 ���� 
	vaddps		xmm0, xmm0, xmm2					; xmm0 = ( ( ( z6 - z4 ) * 2 ) +  ( z3 - z1 ) + ( z9 - z7 ) ) �4 ���� 
													; �.�. xmm0 = ( Gx, Gx, Gx, Gx )
	vmulps		xmm0, xmm0, xmm0					; xmm3 = ( Gx^2, Gx^2, Gx^2, Gx^2 )



; �� �������. 
; �������� ������� xmm0 � xmm3
; ����� ������� ������
; � �������� �� ������ rcx

	vaddps		xmm0, xmm0, xmm3					; xmm0 = ( Gx^2 + Gy^2 ) x4 ����
	vsqrtps		xmm0, xmm0							; xmm0 = ( sqrt ( Gx^2 + Gy^2 ) ) x4 ����
													; �������� �� ������������
	vbroadcastss xmm4, over							; xmm4 = ( 255, 255, 255, 255 )
	vminps		xmm0, xmm0, xmm4					; � ����� ���� �� �����. � ������� ������ �������� ������������ �� ����� �� ������� 
	vcvtps2dq	xmm0, xmm0							; ������������ � �����
	vpextrb		byte ptr [rcx], xmm0, 0				; ������� ������ ���� xmm0 �� ������ �������� z5
	
	
	vmovdqu		ymm6, ymmword ptr[rsp + 32*0]		; ����������� ��������
	vmovdqu		ymm7, ymmword ptr[rsp + 32*1]
	vmovdqu		ymm8, ymmword ptr[rsp + 32*2]
	vmovdqu		ymm9, ymmword ptr[rsp + 32*3]
	vmovdqu		ymm10, ymmword ptr[rsp + 32*4]
	vmovdqu		ymm11, ymmword ptr[rsp + 32*5]
	vmovdqu		ymm12, ymmword ptr[rsp + 32*6]
	vmovdqu		ymm13, ymmword ptr[rsp + 32*7]
	add			rsp, 32*8

	vzeroall										; ������� �������� �� �����
	ret												; � ������� �������
Kernel ENDP
END													; ����� :)
