	.file	"insnsa.c"
	.text
LC0:
	.ascii "\1"
	.ascii "7\0"
	.data
	.align 32
_instrux_AAA:
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC0
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1:
	.ascii "\2\325\12\0"
LC2:
	.ascii "\1\325\24\0"
	.data
	.align 32
_instrux_AAD:
	.long	1
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1
	.long	0
	.long	1
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC2
	.long	4
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC3:
	.ascii "\2\324\12\0"
LC4:
	.ascii "\1\324\24\0"
	.data
	.align 32
_instrux_AAM:
	.long	2
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC3
	.long	0
	.long	2
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC4
	.long	4
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC5:
	.ascii "\1?\0"
	.data
	.align 32
_instrux_AAS:
	.long	3
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC5
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC6:
	.ascii "\300\1\20A\0"
LC7:
	.ascii "\1\20A\0"
LC8:
	.ascii "\320\300\1\21A\0"
LC9:
	.ascii "\320\1\21A\0"
LC10:
	.ascii "\321\300\1\21A\0"
LC11:
	.ascii "\321\1\21A\0"
LC12:
	.ascii "\301\1\22H\0"
LC13:
	.ascii "\1\22H\0"
LC14:
	.ascii "\320\301\1\23H\0"
LC15:
	.ascii "\320\1\23H\0"
LC16:
	.ascii "\321\301\1\23H\0"
LC17:
	.ascii "\321\1\23H\0"
LC18:
	.ascii "\320\300\1\203\202\15\0"
LC19:
	.ascii "\321\300\1\203\202\15\0"
LC20:
	.ascii "\1\24\21\0"
LC21:
	.ascii "\320\1\203\202\15\0"
LC22:
	.ascii "\320\1\25\31\0"
LC23:
	.ascii "\321\1\203\202\15\0"
LC24:
	.ascii "\321\1\25!\0"
LC25:
	.ascii "\300\1\200\202\21\0"
LC26:
	.ascii "\320\300\\\1\201\202Y\0"
LC27:
	.ascii "\321\300d\1\201\202a\0"
	.data
	.align 32
_instrux_ADC:
	.long	4
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC6
	.long	1
	.long	4
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC7
	.long	0
	.long	4
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC8
	.long	1
	.long	4
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC9
	.long	0
	.long	4
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC10
	.long	50331649
	.long	4
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC11
	.long	50331648
	.long	4
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC12
	.long	1
	.long	4
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC13
	.long	0
	.long	4
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC14
	.long	1
	.long	4
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC15
	.long	0
	.long	4
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC16
	.long	50331649
	.long	4
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC17
	.long	50331648
	.long	4
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC18
	.long	0
	.long	4
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC19
	.long	50331648
	.long	4
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC20
	.long	1
	.long	4
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC21
	.long	1
	.long	4
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC22
	.long	1
	.long	4
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC23
	.long	50331649
	.long	4
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC24
	.long	50331649
	.long	4
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC25
	.long	1
	.long	4
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC26
	.long	1
	.long	4
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC27
	.long	50331649
	.long	4
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC25
	.long	1
	.long	4
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC26
	.long	1
	.long	4
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC27
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC28:
	.ascii "\300\17A\0"
LC29:
	.ascii "\17A\0"
LC30:
	.ascii "\320\300\1\1A\0"
LC31:
	.ascii "\320\1\1A\0"
LC32:
	.ascii "\321\300\1\1A\0"
LC33:
	.ascii "\321\1\1A\0"
LC34:
	.ascii "\301\1\2H\0"
LC35:
	.ascii "\1\2H\0"
LC36:
	.ascii "\320\301\1\3H\0"
LC37:
	.ascii "\320\1\3H\0"
LC38:
	.ascii "\321\301\1\3H\0"
LC39:
	.ascii "\321\1\3H\0"
LC40:
	.ascii "\320\300\1\203\200\15\0"
LC41:
	.ascii "\321\300\1\203\200\15\0"
LC42:
	.ascii "\1\4\21\0"
LC43:
	.ascii "\320\1\203\200\15\0"
LC44:
	.ascii "\320\1\5\31\0"
LC45:
	.ascii "\321\1\203\200\15\0"
LC46:
	.ascii "\321\1\5!\0"
LC47:
	.ascii "\300\1\200\200\21\0"
LC48:
	.ascii "\320\300\\\1\201\200Y\0"
LC49:
	.ascii "\321\300d\1\201\200a\0"
	.data
	.align 32
_instrux_ADD:
	.long	5
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC28
	.long	1
	.long	5
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC29
	.long	0
	.long	5
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC30
	.long	1
	.long	5
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC31
	.long	0
	.long	5
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC32
	.long	50331649
	.long	5
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC33
	.long	50331648
	.long	5
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC34
	.long	1
	.long	5
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC35
	.long	0
	.long	5
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC36
	.long	1
	.long	5
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC37
	.long	0
	.long	5
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC38
	.long	50331649
	.long	5
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC39
	.long	50331648
	.long	5
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC40
	.long	0
	.long	5
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC41
	.long	50331648
	.long	5
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC42
	.long	1
	.long	5
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC43
	.long	1
	.long	5
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC44
	.long	1
	.long	5
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC45
	.long	50331649
	.long	5
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC46
	.long	50331649
	.long	5
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC47
	.long	1
	.long	5
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC48
	.long	1
	.long	5
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC49
	.long	50331649
	.long	5
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC47
	.long	1
	.long	5
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC48
	.long	1
	.long	5
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC49
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC50:
	.ascii "\331\3f\17XH\0"
LC51:
	.ascii "\301\331\3f\17XH\0"
	.data
	.align 32
_instrux_ADDPD:
	.long	6
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC50
	.long	134348800
	.long	6
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC51
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC52:
	.ascii "\301\331\2\17XH\0"
LC53:
	.ascii "\331\2\17XH\0"
	.data
	.align 32
_instrux_ADDPS:
	.long	7
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC52
	.long	117506048
	.long	7
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC53
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC54:
	.ascii "\331\3\362\17XH\0"
LC55:
	.ascii "\301\331\3\362\17XH\0"
	.data
	.align 32
_instrux_ADDSD:
	.long	8
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC54
	.long	134348800
	.long	8
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC55
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC56:
	.ascii "\301\333\2\17XH\0"
LC57:
	.ascii "\333\2\17XH\0"
	.data
	.align 32
_instrux_ADDSS:
	.long	9
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC56
	.long	117506048
	.long	9
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC57
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC58:
	.ascii "\301\3f\17\320H\0"
LC59:
	.ascii "\3f\17\320H\0"
	.data
	.align 32
_instrux_ADDSUBPD:
	.long	10
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC58
	.long	151257089
	.long	10
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC59
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC60:
	.ascii "\301\3\362\17\320H\0"
LC61:
	.ascii "\3\362\17\320H\0"
	.data
	.align 32
_instrux_ADDSUBPS:
	.long	11
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC60
	.long	151257089
	.long	11
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC61
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC62:
	.ascii "\300\1 A\0"
LC63:
	.ascii "\1 A\0"
LC64:
	.ascii "\320\300\1!A\0"
LC65:
	.ascii "\320\1!A\0"
LC66:
	.ascii "\321\300\1!A\0"
LC67:
	.ascii "\321\1!A\0"
LC68:
	.ascii "\301\1\"H\0"
LC69:
	.ascii "\1\"H\0"
LC70:
	.ascii "\320\301\1#H\0"
LC71:
	.ascii "\320\1#H\0"
LC72:
	.ascii "\321\301\1#H\0"
LC73:
	.ascii "\321\1#H\0"
LC74:
	.ascii "\320\300\1\203\204\15\0"
LC75:
	.ascii "\321\300\1\203\204\15\0"
LC76:
	.ascii "\1$\21\0"
LC77:
	.ascii "\320\1\203\204\15\0"
LC78:
	.ascii "\320\1%\31\0"
LC79:
	.ascii "\321\1\203\204\15\0"
LC80:
	.ascii "\321\1%!\0"
LC81:
	.ascii "\300\1\200\204\21\0"
LC82:
	.ascii "\320\300\\\1\201\204Y\0"
LC83:
	.ascii "\321\300d\1\201\204a\0"
	.data
	.align 32
_instrux_AND:
	.long	12
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC62
	.long	1
	.long	12
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC63
	.long	0
	.long	12
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC64
	.long	1
	.long	12
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC65
	.long	0
	.long	12
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC66
	.long	50331649
	.long	12
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC67
	.long	50331648
	.long	12
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC68
	.long	1
	.long	12
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC69
	.long	0
	.long	12
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC70
	.long	1
	.long	12
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC71
	.long	0
	.long	12
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC72
	.long	50331649
	.long	12
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC73
	.long	50331648
	.long	12
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC74
	.long	0
	.long	12
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC75
	.long	50331648
	.long	12
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC76
	.long	1
	.long	12
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC77
	.long	1
	.long	12
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC78
	.long	1
	.long	12
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC79
	.long	50331649
	.long	12
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC80
	.long	50331649
	.long	12
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC81
	.long	1
	.long	12
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC82
	.long	1
	.long	12
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC83
	.long	50331649
	.long	12
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC81
	.long	1
	.long	12
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC82
	.long	1
	.long	12
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC83
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC84:
	.ascii "\331\3f\17UH\0"
LC85:
	.ascii "\301\331\3f\17UH\0"
	.data
	.align 32
_instrux_ANDNPD:
	.long	13
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC84
	.long	134348800
	.long	13
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC85
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC86:
	.ascii "\301\2\17UH\0"
LC87:
	.ascii "\2\17UH\0"
	.data
	.align 32
_instrux_ANDNPS:
	.long	14
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC86
	.long	117506048
	.long	14
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC87
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC88:
	.ascii "\331\3f\17TH\0"
LC89:
	.ascii "\301\331\3f\17TH\0"
	.data
	.align 32
_instrux_ANDPD:
	.long	15
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC88
	.long	134348800
	.long	15
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC89
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC90:
	.ascii "\301\2\17TH\0"
LC91:
	.ascii "\2\17TH\0"
	.data
	.align 32
_instrux_ANDPS:
	.long	16
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC90
	.long	117506048
	.long	16
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC91
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC92:
	.ascii "\300\1cA\0"
LC93:
	.ascii "\1cA\0"
	.data
	.align 32
_instrux_ARPL:
	.long	17
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC92
	.long	33555457
	.long	17
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC93
	.long	33555456
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC94:
	.ascii "\320\301\1bH\0"
LC95:
	.ascii "\321\301\1bH\0"
	.data
	.align 32
_instrux_BOUND:
	.long	18
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC94
	.long	16777216
	.long	18
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC95
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC96:
	.ascii "\320\301\2\17\274H\0"
LC97:
	.ascii "\320\2\17\274H\0"
LC98:
	.ascii "\321\301\2\17\274H\0"
LC99:
	.ascii "\321\2\17\274H\0"
	.data
	.align 32
_instrux_BSF:
	.long	19
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC96
	.long	50331649
	.long	19
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC97
	.long	50331648
	.long	19
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC98
	.long	50331649
	.long	19
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC99
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC100:
	.ascii "\320\301\2\17\275H\0"
LC101:
	.ascii "\320\2\17\275H\0"
LC102:
	.ascii "\321\301\2\17\275H\0"
LC103:
	.ascii "\321\2\17\275H\0"
	.data
	.align 32
_instrux_BSR:
	.long	20
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC100
	.long	50331649
	.long	20
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC101
	.long	50331648
	.long	20
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC102
	.long	50331649
	.long	20
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC103
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC104:
	.ascii "\321\1\17\10\310\0"
	.data
	.align 32
_instrux_BSWAP:
	.long	21
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC104
	.long	67108864
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC105:
	.ascii "\320\300\2\17\243A\0"
LC106:
	.ascii "\320\2\17\243A\0"
LC107:
	.ascii "\321\300\2\17\243A\0"
LC108:
	.ascii "\321\2\17\243A\0"
LC109:
	.ascii "\320\300\2\17\272\204\25\0"
LC110:
	.ascii "\321\300\2\17\272\204\25\0"
	.data
	.align 32
_instrux_BT:
	.long	22
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC105
	.long	50331649
	.long	22
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC106
	.long	50331648
	.long	22
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC107
	.long	50331649
	.long	22
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC108
	.long	50331648
	.long	22
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC109
	.long	50331652
	.long	22
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC110
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC111:
	.ascii "\320\300\2\17\273A\0"
LC112:
	.ascii "\320\2\17\273A\0"
LC113:
	.ascii "\321\300\2\17\273A\0"
LC114:
	.ascii "\321\2\17\273A\0"
LC115:
	.ascii "\320\300\2\17\272\207\25\0"
LC116:
	.ascii "\321\300\2\17\272\207\25\0"
	.data
	.align 32
_instrux_BTC:
	.long	23
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC111
	.long	50331649
	.long	23
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC112
	.long	50331648
	.long	23
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC113
	.long	50331649
	.long	23
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC114
	.long	50331648
	.long	23
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC115
	.long	50331652
	.long	23
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC116
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC117:
	.ascii "\320\300\2\17\263A\0"
LC118:
	.ascii "\320\2\17\263A\0"
LC119:
	.ascii "\321\300\2\17\263A\0"
LC120:
	.ascii "\321\2\17\263A\0"
LC121:
	.ascii "\320\300\2\17\272\206\25\0"
LC122:
	.ascii "\321\300\2\17\272\206\25\0"
	.data
	.align 32
_instrux_BTR:
	.long	24
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC117
	.long	50331649
	.long	24
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC118
	.long	50331648
	.long	24
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC119
	.long	50331649
	.long	24
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC120
	.long	50331648
	.long	24
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC121
	.long	50331652
	.long	24
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC122
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC123:
	.ascii "\320\300\2\17\253A\0"
LC124:
	.ascii "\320\2\17\253A\0"
LC125:
	.ascii "\321\300\2\17\253A\0"
LC126:
	.ascii "\321\2\17\253A\0"
LC127:
	.ascii "\320\300\2\17\272\205\25\0"
LC128:
	.ascii "\321\300\2\17\272\205\25\0"
	.data
	.align 32
_instrux_BTS:
	.long	25
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC123
	.long	50331649
	.long	25
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC124
	.long	50331648
	.long	25
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC125
	.long	50331649
	.long	25
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC126
	.long	50331648
	.long	25
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC127
	.long	50331652
	.long	25
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC128
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC129:
	.ascii "\322\1\350"
	.ascii "4\0"
LC130:
	.ascii "\322\1\232\34\37\0"
LC131:
	.ascii "\320\1\350"
	.ascii "4\0"
LC132:
	.ascii "\320\1\232\34\37\0"
LC133:
	.ascii "\321\1\350"
	.ascii "4\0"
LC134:
	.ascii "\321\1\232\34\37\0"
LC135:
	.ascii "\322\1\232\35\30\0"
LC136:
	.ascii "\320\1\232\31\30\0"
LC137:
	.ascii "\321\1\232!\30\0"
LC138:
	.ascii "\322\300\1\377\203\0"
LC139:
	.ascii "\320\300\1\377\203\0"
LC140:
	.ascii "\321\300\1\377\203\0"
LC141:
	.ascii "\322\300\1\377\202\0"
LC142:
	.ascii "\320\300\1\377\202\0"
LC143:
	.ascii "\321\300\1\377\202\0"
	.data
	.align 32
_instrux_CALL:
	.long	26
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC129
	.long	0
	.long	26
	.long	1
	.long	8256
	.long	0
	.long	0
	.long	LC129
	.long	0
	.long	26
	.long	1
	.long	8224
	.long	0
	.long	0
	.long	LC130
	.long	0
	.long	26
	.long	1
	.long	8194
	.long	0
	.long	0
	.long	LC131
	.long	0
	.long	26
	.long	1
	.long	8258
	.long	0
	.long	0
	.long	LC131
	.long	0
	.long	26
	.long	1
	.long	8226
	.long	0
	.long	0
	.long	LC132
	.long	0
	.long	26
	.long	1
	.long	8196
	.long	0
	.long	0
	.long	LC133
	.long	50331648
	.long	26
	.long	1
	.long	8260
	.long	0
	.long	0
	.long	LC133
	.long	50331648
	.long	26
	.long	1
	.long	8228
	.long	0
	.long	0
	.long	LC134
	.long	50331648
	.long	26
	.long	2
	.long	8704
	.long	8192
	.long	0
	.long	LC135
	.long	0
	.long	26
	.long	2
	.long	8706
	.long	8192
	.long	0
	.long	LC136
	.long	0
	.long	26
	.long	2
	.long	8704
	.long	8194
	.long	0
	.long	LC136
	.long	0
	.long	26
	.long	2
	.long	8708
	.long	8192
	.long	0
	.long	LC137
	.long	50331648
	.long	26
	.long	2
	.long	8704
	.long	8196
	.long	0
	.long	LC137
	.long	50331648
	.long	26
	.long	1
	.long	2113568
	.long	0
	.long	0
	.long	LC138
	.long	0
	.long	26
	.long	1
	.long	2113570
	.long	0
	.long	0
	.long	LC139
	.long	0
	.long	26
	.long	1
	.long	2113572
	.long	0
	.long	0
	.long	LC140
	.long	50331648
	.long	26
	.long	1
	.long	2113600
	.long	0
	.long	0
	.long	LC141
	.long	0
	.long	26
	.long	1
	.long	2113602
	.long	0
	.long	0
	.long	LC142
	.long	0
	.long	26
	.long	1
	.long	2113604
	.long	0
	.long	0
	.long	LC143
	.long	50331648
	.long	26
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC142
	.long	0
	.long	26
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC143
	.long	50331648
	.long	26
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC141
	.long	0
	.long	26
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC142
	.long	0
	.long	26
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC143
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC144:
	.ascii "\320\1\230\0"
	.data
	.align 32
_instrux_CBW:
	.long	27
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC144
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC145:
	.ascii "\321\1\231\0"
	.data
	.align 32
_instrux_CDQ:
	.long	28
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC145
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC146:
	.ascii "\1\370\0"
	.data
	.align 32
_instrux_CLC:
	.long	29
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC146
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC147:
	.ascii "\1\374\0"
	.data
	.align 32
_instrux_CLD:
	.long	30
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC147
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC148:
	.ascii "\300\2\17\256\207\0"
	.data
	.align 32
_instrux_CLFLUSH:
	.long	31
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC148
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC149:
	.ascii "\1\372\0"
	.data
	.align 32
_instrux_CLI:
	.long	32
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC149
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC150:
	.ascii "\2\17\6\0"
	.data
	.align 32
_instrux_CLTS:
	.long	33
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC150
	.long	33554688
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC151:
	.ascii "\1\365\0"
	.data
	.align 32
_instrux_CMC:
	.long	34
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC151
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC152:
	.ascii "\300\1"
	.ascii "8A\0"
LC153:
	.ascii "\1"
	.ascii "8A\0"
LC154:
	.ascii "\320\300\1"
	.ascii "9A\0"
LC155:
	.ascii "\320\1"
	.ascii "9A\0"
LC156:
	.ascii "\321\300\1"
	.ascii "9A\0"
LC157:
	.ascii "\321\1"
	.ascii "9A\0"
LC158:
	.ascii "\301\1:H\0"
LC159:
	.ascii "\1:H\0"
LC160:
	.ascii "\320\301\1;H\0"
LC161:
	.ascii "\320\1;H\0"
LC162:
	.ascii "\321\301\1;H\0"
LC163:
	.ascii "\321\1;H\0"
LC164:
	.ascii "\320\300\1\203\207\15\0"
LC165:
	.ascii "\321\300\1\203\207\15\0"
LC166:
	.ascii "\1<\21\0"
LC167:
	.ascii "\320\1\203\207\15\0"
LC168:
	.ascii "\320\1=\31\0"
LC169:
	.ascii "\321\1\203\207\15\0"
LC170:
	.ascii "\321\1=!\0"
LC171:
	.ascii "\300\1\200\207\21\0"
LC172:
	.ascii "\320\300\\\1\201\207Y\0"
LC173:
	.ascii "\321\300d\1\201\207a\0"
	.data
	.align 32
_instrux_CMP:
	.long	35
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC152
	.long	1
	.long	35
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC153
	.long	0
	.long	35
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC154
	.long	1
	.long	35
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC155
	.long	0
	.long	35
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC156
	.long	50331649
	.long	35
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC157
	.long	50331648
	.long	35
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC158
	.long	1
	.long	35
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC159
	.long	0
	.long	35
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC160
	.long	1
	.long	35
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC161
	.long	0
	.long	35
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC162
	.long	50331649
	.long	35
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC163
	.long	50331648
	.long	35
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC164
	.long	0
	.long	35
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC165
	.long	50331648
	.long	35
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC166
	.long	1
	.long	35
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC167
	.long	1
	.long	35
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC168
	.long	1
	.long	35
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC169
	.long	50331649
	.long	35
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC170
	.long	50331649
	.long	35
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC171
	.long	1
	.long	35
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC172
	.long	1
	.long	35
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC173
	.long	50331649
	.long	35
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC171
	.long	1
	.long	35
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC172
	.long	1
	.long	35
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC173
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC174:
	.ascii "\301\331\3f\17\302H\1\0\0"
LC175:
	.ascii "\331\3f\17\302H\1\0\0"
	.data
	.align 32
_instrux_CMPEQPD:
	.long	36
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC174
	.long	134348801
	.long	36
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC175
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC176:
	.ascii "\301\331\2\17\302H\1\0\0"
LC177:
	.ascii "\331\2\17\302H\1\0\0"
	.data
	.align 32
_instrux_CMPEQPS:
	.long	37
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC176
	.long	117506048
	.long	37
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC177
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC178:
	.ascii "\301\331\3\362\17\302H\1\0\0"
LC179:
	.ascii "\331\3\362\17\302H\1\0\0"
	.data
	.align 32
_instrux_CMPEQSD:
	.long	38
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC178
	.long	134348800
	.long	38
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC179
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC180:
	.ascii "\301\333\2\17\302H\1\0\0"
LC181:
	.ascii "\333\2\17\302H\1\0\0"
	.data
	.align 32
_instrux_CMPEQSS:
	.long	39
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC180
	.long	117506048
	.long	39
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC181
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC182:
	.ascii "\301\331\3f\17\302H\1\2\0"
LC183:
	.ascii "\331\3f\17\302H\1\2\0"
	.data
	.align 32
_instrux_CMPLEPD:
	.long	40
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC182
	.long	134348801
	.long	40
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC183
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC184:
	.ascii "\301\331\2\17\302H\1\2\0"
LC185:
	.ascii "\331\2\17\302H\1\2\0"
	.data
	.align 32
_instrux_CMPLEPS:
	.long	41
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC184
	.long	117506048
	.long	41
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC185
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC186:
	.ascii "\301\331\3\362\17\302H\1\2\0"
LC187:
	.ascii "\331\3\362\17\302H\1\2\0"
	.data
	.align 32
_instrux_CMPLESD:
	.long	42
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC186
	.long	134348800
	.long	42
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC187
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC188:
	.ascii "\301\333\2\17\302H\1\2\0"
LC189:
	.ascii "\333\2\17\302H\1\2\0"
	.data
	.align 32
_instrux_CMPLESS:
	.long	43
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC188
	.long	117506048
	.long	43
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC189
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC190:
	.ascii "\301\331\3f\17\302H\1\1\0"
LC191:
	.ascii "\331\3f\17\302H\1\1\0"
	.data
	.align 32
_instrux_CMPLTPD:
	.long	44
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC190
	.long	134348801
	.long	44
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC191
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC192:
	.ascii "\301\331\2\17\302H\1\1\0"
LC193:
	.ascii "\331\2\17\302H\1\1\0"
	.data
	.align 32
_instrux_CMPLTPS:
	.long	45
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC192
	.long	117506048
	.long	45
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC193
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC194:
	.ascii "\301\331\3\362\17\302H\1\1\0"
LC195:
	.ascii "\331\3\362\17\302H\1\1\0"
	.data
	.align 32
_instrux_CMPLTSD:
	.long	46
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC194
	.long	134348800
	.long	46
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC195
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC196:
	.ascii "\301\333\2\17\302H\1\1\0"
LC197:
	.ascii "\333\2\17\302H\1\1\0"
	.data
	.align 32
_instrux_CMPLTSS:
	.long	47
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC196
	.long	117506048
	.long	47
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC197
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC198:
	.ascii "\301\331\3f\17\302H\1\4\0"
LC199:
	.ascii "\331\3f\17\302H\1\4\0"
	.data
	.align 32
_instrux_CMPNEQPD:
	.long	48
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC198
	.long	134348801
	.long	48
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC199
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC200:
	.ascii "\301\331\2\17\302H\1\4\0"
LC201:
	.ascii "\331\2\17\302H\1\4\0"
	.data
	.align 32
_instrux_CMPNEQPS:
	.long	49
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC200
	.long	117506048
	.long	49
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC201
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC202:
	.ascii "\301\331\3\362\17\302H\1\4\0"
LC203:
	.ascii "\331\3\362\17\302H\1\4\0"
	.data
	.align 32
_instrux_CMPNEQSD:
	.long	50
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC202
	.long	134348800
	.long	50
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC203
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC204:
	.ascii "\301\333\2\17\302H\1\4\0"
LC205:
	.ascii "\333\2\17\302H\1\4\0"
	.data
	.align 32
_instrux_CMPNEQSS:
	.long	51
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC204
	.long	117506048
	.long	51
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC205
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC206:
	.ascii "\301\331\3f\17\302H\1\6\0"
LC207:
	.ascii "\331\3f\17\302H\1\6\0"
	.data
	.align 32
_instrux_CMPNLEPD:
	.long	52
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC206
	.long	134348801
	.long	52
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC207
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC208:
	.ascii "\301\331\2\17\302H\1\6\0"
LC209:
	.ascii "\331\2\17\302H\1\6\0"
	.data
	.align 32
_instrux_CMPNLEPS:
	.long	53
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC208
	.long	117506048
	.long	53
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC209
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC210:
	.ascii "\301\331\3\362\17\302H\1\6\0"
LC211:
	.ascii "\331\3\362\17\302H\1\6\0"
	.data
	.align 32
_instrux_CMPNLESD:
	.long	54
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC210
	.long	134348800
	.long	54
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC211
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC212:
	.ascii "\301\333\2\17\302H\1\6\0"
LC213:
	.ascii "\333\2\17\302H\1\6\0"
	.data
	.align 32
_instrux_CMPNLESS:
	.long	55
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC212
	.long	117506048
	.long	55
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC213
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC214:
	.ascii "\301\331\3f\17\302H\1\5\0"
LC215:
	.ascii "\331\3f\17\302H\1\5\0"
	.data
	.align 32
_instrux_CMPNLTPD:
	.long	56
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC214
	.long	134348801
	.long	56
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC215
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC216:
	.ascii "\301\331\2\17\302H\1\5\0"
LC217:
	.ascii "\331\2\17\302H\1\5\0"
	.data
	.align 32
_instrux_CMPNLTPS:
	.long	57
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC216
	.long	117506048
	.long	57
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC217
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC218:
	.ascii "\301\331\3\362\17\302H\1\5\0"
LC219:
	.ascii "\331\3\362\17\302H\1\5\0"
	.data
	.align 32
_instrux_CMPNLTSD:
	.long	58
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC218
	.long	134348800
	.long	58
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC219
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC220:
	.ascii "\301\333\2\17\302H\1\5\0"
LC221:
	.ascii "\333\2\17\302H\1\5\0"
	.data
	.align 32
_instrux_CMPNLTSS:
	.long	59
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC220
	.long	117506048
	.long	59
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC221
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC222:
	.ascii "\301\331\3f\17\302H\1\7\0"
LC223:
	.ascii "\331\3f\17\302H\1\7\0"
	.data
	.align 32
_instrux_CMPORDPD:
	.long	60
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC222
	.long	134348801
	.long	60
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC223
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC224:
	.ascii "\301\331\2\17\302H\1\7\0"
LC225:
	.ascii "\331\2\17\302H\1\7\0"
	.data
	.align 32
_instrux_CMPORDPS:
	.long	61
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC224
	.long	117506048
	.long	61
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC225
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC226:
	.ascii "\301\331\3\362\17\302H\1\7\0"
LC227:
	.ascii "\331\3\362\17\302H\1\7\0"
	.data
	.align 32
_instrux_CMPORDSD:
	.long	62
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC226
	.long	134348800
	.long	62
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC227
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC228:
	.ascii "\301\333\2\17\302H\1\7\0"
LC229:
	.ascii "\333\2\17\302H\1\7\0"
	.data
	.align 32
_instrux_CMPORDSS:
	.long	63
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC228
	.long	117506048
	.long	63
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC229
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC230:
	.ascii "\331\3f\17\302H\26\0"
LC231:
	.ascii "\301\331\3f\17\302H\26\0"
	.data
	.align 32
_instrux_CMPPD:
	.long	64
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC230
	.long	134348900
	.long	64
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC231
	.long	134348902
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC232:
	.ascii "\301\331\2\17\302H\26\0"
LC233:
	.ascii "\331\2\17\302H\26\0"
	.data
	.align 32
_instrux_CMPPS:
	.long	65
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC232
	.long	117506148
	.long	65
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC233
	.long	117506148
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC234:
	.ascii "\332\1\246\0"
	.data
	.align 32
_instrux_CMPSB:
	.long	66
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC234
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC235:
	.ascii "\332\321\1\247\0"
LC236:
	.ascii "\331\3\362\17\302H\26\0"
LC237:
	.ascii "\301\331\3\362\17\302H\26\0"
	.data
	.align 32
_instrux_CMPSD:
	.long	67
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC235
	.long	50331648
	.long	67
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC236
	.long	134348900
	.long	67
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC237
	.long	134348900
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC238:
	.ascii "\301\333\2\17\302H\26\0"
LC239:
	.ascii "\333\2\17\302H\26\0"
	.data
	.align 32
_instrux_CMPSS:
	.long	68
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC238
	.long	117506148
	.long	68
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC239
	.long	117506148
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC240:
	.ascii "\332\320\1\247\0"
	.data
	.align 32
_instrux_CMPSW:
	.long	69
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC240
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC241:
	.ascii "\301\331\3f\17\302H\1\3\0"
LC242:
	.ascii "\331\3f\17\302H\1\3\0"
	.data
	.align 32
_instrux_CMPUNORDPD:
	.long	70
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC241
	.long	134348801
	.long	70
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC242
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC243:
	.ascii "\301\331\2\17\302H\1\3\0"
LC244:
	.ascii "\331\2\17\302H\1\3\0"
	.data
	.align 32
_instrux_CMPUNORDPS:
	.long	71
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC243
	.long	117506048
	.long	71
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC244
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC245:
	.ascii "\301\331\3\362\17\302H\1\3\0"
LC246:
	.ascii "\331\3\362\17\302H\1\3\0"
	.data
	.align 32
_instrux_CMPUNORDSD:
	.long	72
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC245
	.long	134348800
	.long	72
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC246
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC247:
	.ascii "\301\333\2\17\302H\1\3\0"
LC248:
	.ascii "\333\2\17\302H\1\3\0"
	.data
	.align 32
_instrux_CMPUNORDSS:
	.long	73
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC247
	.long	117506048
	.long	73
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC248
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC249:
	.ascii "\300\2\17\260A\0"
LC250:
	.ascii "\2\17\260A\0"
LC251:
	.ascii "\320\300\2\17\261A\0"
LC252:
	.ascii "\320\2\17\261A\0"
LC253:
	.ascii "\321\300\2\17\261A\0"
LC254:
	.ascii "\321\2\17\261A\0"
	.data
	.align 32
_instrux_CMPXCHG:
	.long	74
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC249
	.long	83886081
	.long	74
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC250
	.long	83886080
	.long	74
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC251
	.long	83886081
	.long	74
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC252
	.long	83886080
	.long	74
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC253
	.long	83886081
	.long	74
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC254
	.long	83886080
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC255:
	.ascii "\300\2\17\246A\0"
LC256:
	.ascii "\2\17\246A\0"
LC257:
	.ascii "\320\300\2\17\247A\0"
LC258:
	.ascii "\320\2\17\247A\0"
LC259:
	.ascii "\321\300\2\17\247A\0"
LC260:
	.ascii "\321\2\17\247A\0"
	.data
	.align 32
_instrux_CMPXCHG486:
	.long	75
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC255
	.long	67112961
	.long	75
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC256
	.long	67112960
	.long	75
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC257
	.long	67112961
	.long	75
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC258
	.long	67112960
	.long	75
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC259
	.long	67112961
	.long	75
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC260
	.long	67112960
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC261:
	.ascii "\300\2\17\307\201\0"
	.data
	.align 32
_instrux_CMPXCHG8B:
	.long	76
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC261
	.long	83886080
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC262:
	.ascii "\331\3f\17/H\0"
LC263:
	.ascii "\301\331\3f\17/H\0"
	.data
	.align 32
_instrux_COMISD:
	.long	77
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC262
	.long	134348800
	.long	77
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC263
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC264:
	.ascii "\301\2\17/H\0"
LC265:
	.ascii "\2\17/H\0"
	.data
	.align 32
_instrux_COMISS:
	.long	78
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC264
	.long	117506048
	.long	78
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC265
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC266:
	.ascii "\2\17\242\0"
	.data
	.align 32
_instrux_CPUID:
	.long	79
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC266
	.long	83886080
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC267:
	.ascii "\333\2\17\346H\0"
LC268:
	.ascii "\301\333\2\17\346H\0"
	.data
	.align 32
_instrux_CVTDQ2PD:
	.long	80
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC267
	.long	134348800
	.long	80
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC268
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC269:
	.ascii "\2\17[H\0"
LC270:
	.ascii "\301\2\17[H\0"
	.data
	.align 32
_instrux_CVTDQ2PS:
	.long	81
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC269
	.long	134348800
	.long	81
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC270
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC271:
	.ascii "\3\362\17\346H\0"
LC272:
	.ascii "\301\3\362\17\346H\0"
	.data
	.align 32
_instrux_CVTPD2DQ:
	.long	82
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC271
	.long	134348800
	.long	82
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC272
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC273:
	.ascii "\3f\17-H\0"
LC274:
	.ascii "\301\3f\17-H\0"
	.data
	.align 32
_instrux_CVTPD2PI:
	.long	83
	.long	2
	.long	2101256
	.long	2101264
	.long	0
	.long	LC273
	.long	134348800
	.long	83
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC274
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC275:
	.ascii "\3f\17ZH\0"
LC276:
	.ascii "\301\3f\17ZH\0"
	.data
	.align 32
_instrux_CVTPD2PS:
	.long	84
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC275
	.long	134348800
	.long	84
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC276
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC277:
	.ascii "\3f\17*H\0"
LC278:
	.ascii "\301\3f\17*H\0"
	.data
	.align 32
_instrux_CVTPI2PD:
	.long	85
	.long	2
	.long	2101264
	.long	2101256
	.long	0
	.long	LC277
	.long	134348800
	.long	85
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC278
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC279:
	.ascii "\301\331\2\17*H\0"
LC280:
	.ascii "\331\2\17*H\0"
	.data
	.align 32
_instrux_CVTPI2PS:
	.long	86
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC279
	.long	117522432
	.long	86
	.long	2
	.long	2101264
	.long	2101256
	.long	0
	.long	LC280
	.long	117522432
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC281:
	.ascii "\3f\17[H\0"
LC282:
	.ascii "\301\3f\17[H\0"
	.data
	.align 32
_instrux_CVTPS2DQ:
	.long	87
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC281
	.long	134348800
	.long	87
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC282
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC283:
	.ascii "\2\17ZH\0"
LC284:
	.ascii "\301\2\17ZH\0"
	.data
	.align 32
_instrux_CVTPS2PD:
	.long	88
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC283
	.long	134348800
	.long	88
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC284
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC285:
	.ascii "\301\331\2\17-H\0"
LC286:
	.ascii "\331\2\17-H\0"
	.data
	.align 32
_instrux_CVTPS2PI:
	.long	89
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC285
	.long	117522432
	.long	89
	.long	2
	.long	2101256
	.long	2101264
	.long	0
	.long	LC286
	.long	117522432
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC287:
	.ascii "\3\362\17-H\0"
LC288:
	.ascii "\301\3\362\17-H\0"
	.data
	.align 32
_instrux_CVTSD2SI:
	.long	90
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC287
	.long	134348800
	.long	90
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC288
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC289:
	.ascii "\3\362\17ZH\0"
LC290:
	.ascii "\301\3\362\17ZH\0"
	.data
	.align 32
_instrux_CVTSD2SS:
	.long	91
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC289
	.long	134348800
	.long	91
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC290
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC291:
	.ascii "\3\362\17*H\0"
LC292:
	.ascii "\301\3\362\17*H\0"
	.data
	.align 32
_instrux_CVTSI2SD:
	.long	92
	.long	2
	.long	2101264
	.long	2101252
	.long	0
	.long	LC291
	.long	134348800
	.long	92
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC292
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC293:
	.ascii "\301\333\2\17*H\0"
LC294:
	.ascii "\333\2\17*H\0"
	.data
	.align 32
_instrux_CVTSI2SS:
	.long	93
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC293
	.long	117506128
	.long	93
	.long	2
	.long	2101264
	.long	2101252
	.long	0
	.long	LC294
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC295:
	.ascii "\333\2\17ZH\0"
LC296:
	.ascii "\301\333\2\17ZH\0"
	.data
	.align 32
_instrux_CVTSS2SD:
	.long	94
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC295
	.long	134348800
	.long	94
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC296
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC297:
	.ascii "\301\333\2\17-H\0"
LC298:
	.ascii "\333\2\17-H\0"
	.data
	.align 32
_instrux_CVTSS2SI:
	.long	95
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC297
	.long	117506048
	.long	95
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC298
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC299:
	.ascii "\3f\17\346H\0"
LC300:
	.ascii "\301\3f\17\346H\0"
	.data
	.align 32
_instrux_CVTTPD2DQ:
	.long	96
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC299
	.long	134348800
	.long	96
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC300
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC301:
	.ascii "\3f\17,H\0"
LC302:
	.ascii "\301\3f\17,H\0"
	.data
	.align 32
_instrux_CVTTPD2PI:
	.long	97
	.long	2
	.long	2101256
	.long	2101264
	.long	0
	.long	LC301
	.long	134348800
	.long	97
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC302
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC303:
	.ascii "\333\2\17[H\0"
LC304:
	.ascii "\301\333\2\17[H\0"
	.data
	.align 32
_instrux_CVTTPS2DQ:
	.long	98
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC303
	.long	134348800
	.long	98
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC304
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC305:
	.ascii "\301\331\2\17,H\0"
LC306:
	.ascii "\331\2\17,H\0"
	.data
	.align 32
_instrux_CVTTPS2PI:
	.long	99
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC305
	.long	117522432
	.long	99
	.long	2
	.long	2101256
	.long	2101264
	.long	0
	.long	LC306
	.long	117522432
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC307:
	.ascii "\3\362\17,H\0"
LC308:
	.ascii "\301\3\362\17,H\0"
	.data
	.align 32
_instrux_CVTTSD2SI:
	.long	100
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC307
	.long	134348800
	.long	100
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC308
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC309:
	.ascii "\301\333\2\17,H\0"
LC310:
	.ascii "\333\2\17,H\0"
	.data
	.align 32
_instrux_CVTTSS2SI:
	.long	101
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC309
	.long	117506048
	.long	101
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC310
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC311:
	.ascii "\320\1\231\0"
	.data
	.align 32
_instrux_CWD:
	.long	102
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC311
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC312:
	.ascii "\321\1\230\0"
	.data
	.align 32
_instrux_CWDE:
	.long	103
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC312
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC313:
	.ascii "\1'\0"
	.data
	.align 32
_instrux_DAA:
	.long	104
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC313
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC314:
	.ascii "\1/\0"
	.data
	.align 32
_instrux_DAS:
	.long	105
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC314
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_DB:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_DD:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC315:
	.ascii "\320\10H\0"
LC316:
	.ascii "\321\10H\0"
LC317:
	.ascii "\300\1\376\201\0"
LC318:
	.ascii "\320\300\1\377\201\0"
LC319:
	.ascii "\321\300\1\377\201\0"
	.data
	.align 32
_instrux_DEC:
	.long	108
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC315
	.long	0
	.long	108
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC316
	.long	50331648
	.long	108
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC317
	.long	0
	.long	108
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC318
	.long	0
	.long	108
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC319
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC320:
	.ascii "\300\1\366\206\0"
LC321:
	.ascii "\320\300\1\367\206\0"
LC322:
	.ascii "\321\300\1\367\206\0"
	.data
	.align 32
_instrux_DIV:
	.long	109
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC320
	.long	0
	.long	109
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC321
	.long	0
	.long	109
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC322
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC323:
	.ascii "\3f\17^H\0"
LC324:
	.ascii "\301\3f\17^H\0"
	.data
	.align 32
_instrux_DIVPD:
	.long	110
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC323
	.long	134348800
	.long	110
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC324
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC325:
	.ascii "\301\331\2\17^H\0"
LC326:
	.ascii "\331\2\17^H\0"
	.data
	.align 32
_instrux_DIVPS:
	.long	111
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC325
	.long	117506048
	.long	111
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC326
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC327:
	.ascii "\3\362\17^H\0"
LC328:
	.ascii "\301\3\362\17^H\0"
	.data
	.align 32
_instrux_DIVSD:
	.long	112
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC327
	.long	134348800
	.long	112
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC328
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC329:
	.ascii "\301\333\2\17^H\0"
LC330:
	.ascii "\333\2\17^H\0"
	.data
	.align 32
_instrux_DIVSS:
	.long	113
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC329
	.long	117506048
	.long	113
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC330
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_DQ:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_DT:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_DW:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC331:
	.ascii "\2\17w\0"
	.data
	.align 32
_instrux_EMMS:
	.long	117
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC331
	.long	83902464
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC332:
	.ascii "\1\310\30\25\0"
	.data
	.align 32
_instrux_ENTER:
	.long	118
	.long	2
	.long	8192
	.long	8192
	.long	0
	.long	LC332
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC333:
	.ascii "\0\0"
	.data
	.align 32
_instrux_EQU:
	.long	119
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC333
	.long	0
	.long	119
	.long	2
	.long	8704
	.long	8192
	.long	0
	.long	LC333
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC334:
	.ascii "\2\331\360\0"
	.data
	.align 32
_instrux_F2XM1:
	.long	120
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC334
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC335:
	.ascii "\2\331\341\0"
	.data
	.align 32
_instrux_FABS:
	.long	121
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC335
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC336:
	.ascii "\300\1\330\200\0"
LC337:
	.ascii "\300\1\334\200\0"
LC338:
	.ascii "\1\334\10\300\0"
LC339:
	.ascii "\1\330\10\300\0"
LC340:
	.ascii "\1\330\11\300\0"
	.data
	.align 32
_instrux_FADD:
	.long	122
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC336
	.long	8192
	.long	122
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC337
	.long	8192
	.long	122
	.long	1
	.long	16777472
	.long	0
	.long	0
	.long	LC338
	.long	8192
	.long	122
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC339
	.long	8192
	.long	122
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC338
	.long	8192
	.long	122
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC340
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC341:
	.ascii "\1\336\10\300\0"
	.data
	.align 32
_instrux_FADDP:
	.long	123
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC341
	.long	8192
	.long	123
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC341
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC342:
	.ascii "\300\1\337\204\0"
	.data
	.align 32
_instrux_FBLD:
	.long	124
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC342
	.long	8192
	.long	124
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC342
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC343:
	.ascii "\300\1\337\206\0"
	.data
	.align 32
_instrux_FBSTP:
	.long	125
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC343
	.long	8192
	.long	125
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC343
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC344:
	.ascii "\2\331\340\0"
	.data
	.align 32
_instrux_FCHS:
	.long	126
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC344
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC345:
	.ascii "\3\233\333\342\0"
	.data
	.align 32
_instrux_FCLEX:
	.long	127
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC345
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC346:
	.ascii "\1\332\10\300\0"
LC347:
	.ascii "\1\332\11\300\0"
	.data
	.align 32
_instrux_FCMOVB:
	.long	128
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC346
	.long	100671488
	.long	128
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC347
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC348:
	.ascii "\1\332\10\320\0"
LC349:
	.ascii "\1\332\11\320\0"
	.data
	.align 32
_instrux_FCMOVBE:
	.long	129
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC348
	.long	100671488
	.long	129
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC349
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC350:
	.ascii "\1\332\10\310\0"
LC351:
	.ascii "\1\332\11\310\0"
	.data
	.align 32
_instrux_FCMOVE:
	.long	130
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC350
	.long	100671488
	.long	130
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC351
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC352:
	.ascii "\1\333\10\300\0"
LC353:
	.ascii "\1\333\11\300\0"
	.data
	.align 32
_instrux_FCMOVNB:
	.long	131
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC352
	.long	100671488
	.long	131
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC353
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC354:
	.ascii "\1\333\10\320\0"
LC355:
	.ascii "\1\333\11\320\0"
	.data
	.align 32
_instrux_FCMOVNBE:
	.long	132
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC354
	.long	100671488
	.long	132
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC355
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC356:
	.ascii "\1\333\10\310\0"
LC357:
	.ascii "\1\333\11\310\0"
	.data
	.align 32
_instrux_FCMOVNE:
	.long	133
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC356
	.long	100671488
	.long	133
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC357
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC358:
	.ascii "\1\333\10\330\0"
LC359:
	.ascii "\1\333\11\330\0"
	.data
	.align 32
_instrux_FCMOVNU:
	.long	134
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC358
	.long	100671488
	.long	134
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC359
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC360:
	.ascii "\1\332\10\330\0"
LC361:
	.ascii "\1\332\11\330\0"
	.data
	.align 32
_instrux_FCMOVU:
	.long	135
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC360
	.long	100671488
	.long	135
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC361
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC362:
	.ascii "\300\1\330\202\0"
LC363:
	.ascii "\300\1\334\202\0"
LC364:
	.ascii "\1\330\10\320\0"
LC365:
	.ascii "\1\330\11\320\0"
	.data
	.align 32
_instrux_FCOM:
	.long	136
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC362
	.long	8192
	.long	136
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC363
	.long	8192
	.long	136
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC364
	.long	8192
	.long	136
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC365
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC366:
	.ascii "\1\333\10\360\0"
LC367:
	.ascii "\1\333\11\360\0"
	.data
	.align 32
_instrux_FCOMI:
	.long	137
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC366
	.long	100671488
	.long	137
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC367
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC368:
	.ascii "\1\337\10\360\0"
LC369:
	.ascii "\1\337\11\360\0"
	.data
	.align 32
_instrux_FCOMIP:
	.long	138
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC368
	.long	100671488
	.long	138
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC369
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC370:
	.ascii "\300\1\330\203\0"
LC371:
	.ascii "\300\1\334\203\0"
LC372:
	.ascii "\1\330\10\330\0"
LC373:
	.ascii "\1\330\11\330\0"
	.data
	.align 32
_instrux_FCOMP:
	.long	139
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC370
	.long	8192
	.long	139
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC371
	.long	8192
	.long	139
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC372
	.long	8192
	.long	139
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC373
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC374:
	.ascii "\2\336\331\0"
	.data
	.align 32
_instrux_FCOMPP:
	.long	140
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC374
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC375:
	.ascii "\2\331\377\0"
	.data
	.align 32
_instrux_FCOS:
	.long	141
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC375
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC376:
	.ascii "\2\331\366\0"
	.data
	.align 32
_instrux_FDECSTP:
	.long	142
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC376
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC377:
	.ascii "\3\233\333\341\0"
	.data
	.align 32
_instrux_FDISI:
	.long	143
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC377
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC378:
	.ascii "\300\1\330\206\0"
LC379:
	.ascii "\300\1\334\206\0"
LC380:
	.ascii "\1\334\10\370\0"
LC381:
	.ascii "\1\330\10\360\0"
LC382:
	.ascii "\1\330\11\360\0"
	.data
	.align 32
_instrux_FDIV:
	.long	144
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC378
	.long	8192
	.long	144
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC379
	.long	8192
	.long	144
	.long	1
	.long	16777472
	.long	0
	.long	0
	.long	LC380
	.long	8192
	.long	144
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC380
	.long	8192
	.long	144
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC381
	.long	8192
	.long	144
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC382
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC383:
	.ascii "\1\336\10\370\0"
	.data
	.align 32
_instrux_FDIVP:
	.long	145
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC383
	.long	8192
	.long	145
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC383
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC384:
	.ascii "\300\1\330\207\0"
LC385:
	.ascii "\300\1\334\207\0"
LC386:
	.ascii "\1\334\10\360\0"
LC387:
	.ascii "\1\330\10\370\0"
LC388:
	.ascii "\1\330\11\370\0"
	.data
	.align 32
_instrux_FDIVR:
	.long	146
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC384
	.long	8192
	.long	146
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC385
	.long	8192
	.long	146
	.long	1
	.long	16777472
	.long	0
	.long	0
	.long	LC386
	.long	8192
	.long	146
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC386
	.long	8192
	.long	146
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC387
	.long	8192
	.long	146
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC388
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC389:
	.ascii "\1\336\10\360\0"
	.data
	.align 32
_instrux_FDIVRP:
	.long	147
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC389
	.long	8192
	.long	147
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC389
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC390:
	.ascii "\2\17\16\0"
	.data
	.align 32
_instrux_FEMMS:
	.long	148
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC390
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC391:
	.ascii "\3\233\333\340\0"
	.data
	.align 32
_instrux_FENI:
	.long	149
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC391
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC392:
	.ascii "\1\335\10\300\0"
	.data
	.align 32
_instrux_FFREE:
	.long	150
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC392
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC393:
	.ascii "\1\337\10\300\0"
	.data
	.align 32
_instrux_FFREEP:
	.long	151
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC393
	.long	33566720
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC394:
	.ascii "\300\1\332\200\0"
LC395:
	.ascii "\300\1\336\200\0"
	.data
	.align 32
_instrux_FIADD:
	.long	152
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC394
	.long	8192
	.long	152
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC395
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC396:
	.ascii "\300\1\332\202\0"
LC397:
	.ascii "\300\1\336\202\0"
	.data
	.align 32
_instrux_FICOM:
	.long	153
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC396
	.long	8192
	.long	153
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC397
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC398:
	.ascii "\300\1\332\203\0"
LC399:
	.ascii "\300\1\336\203\0"
	.data
	.align 32
_instrux_FICOMP:
	.long	154
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC398
	.long	8192
	.long	154
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC399
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC400:
	.ascii "\300\1\332\206\0"
LC401:
	.ascii "\300\1\336\206\0"
	.data
	.align 32
_instrux_FIDIV:
	.long	155
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC400
	.long	8192
	.long	155
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC401
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC402:
	.ascii "\300\1\332\207\0"
LC403:
	.ascii "\300\1\336\207\0"
	.data
	.align 32
_instrux_FIDIVR:
	.long	156
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC402
	.long	8192
	.long	156
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC403
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC404:
	.ascii "\300\1\333\200\0"
LC405:
	.ascii "\300\1\337\200\0"
LC406:
	.ascii "\300\1\337\205\0"
	.data
	.align 32
_instrux_FILD:
	.long	157
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC404
	.long	8192
	.long	157
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC405
	.long	8192
	.long	157
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC406
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC407:
	.ascii "\300\1\332\201\0"
LC408:
	.ascii "\300\1\336\201\0"
	.data
	.align 32
_instrux_FIMUL:
	.long	158
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC407
	.long	8192
	.long	158
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC408
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC409:
	.ascii "\2\331\367\0"
	.data
	.align 32
_instrux_FINCSTP:
	.long	159
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC409
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC410:
	.ascii "\3\233\333\343\0"
	.data
	.align 32
_instrux_FINIT:
	.long	160
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC410
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC411:
	.ascii "\300\1\333\202\0"
LC412:
	.ascii "\300\1\337\202\0"
	.data
	.align 32
_instrux_FIST:
	.long	161
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC411
	.long	8192
	.long	161
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC412
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC413:
	.ascii "\300\1\333\203\0"
LC414:
	.ascii "\300\1\337\203\0"
LC415:
	.ascii "\300\1\337\207\0"
	.data
	.align 32
_instrux_FISTP:
	.long	162
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC413
	.long	8192
	.long	162
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC414
	.long	8192
	.long	162
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC415
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC416:
	.ascii "\300\1\335\201\0"
LC417:
	.ascii "\300\1\333\201\0"
LC418:
	.ascii "\300\1\337\201\0"
	.data
	.align 32
_instrux_FISTTP:
	.long	163
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC416
	.long	151003136
	.long	163
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC417
	.long	151003136
	.long	163
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC418
	.long	151003136
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC419:
	.ascii "\300\1\332\204\0"
LC420:
	.ascii "\300\1\336\204\0"
	.data
	.align 32
_instrux_FISUB:
	.long	164
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC419
	.long	8192
	.long	164
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC420
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC421:
	.ascii "\300\1\332\205\0"
LC422:
	.ascii "\300\1\336\205\0"
	.data
	.align 32
_instrux_FISUBR:
	.long	165
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC421
	.long	8192
	.long	165
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC422
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC423:
	.ascii "\300\1\331\200\0"
LC424:
	.ascii "\300\1\335\200\0"
LC425:
	.ascii "\300\1\333\205\0"
LC426:
	.ascii "\1\331\10\300\0"
	.data
	.align 32
_instrux_FLD:
	.long	166
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC423
	.long	8192
	.long	166
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC424
	.long	8192
	.long	166
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC425
	.long	8192
	.long	166
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC426
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC427:
	.ascii "\2\331\350\0"
	.data
	.align 32
_instrux_FLD1:
	.long	167
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC427
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC428:
	.ascii "\300\1\331\205\0"
	.data
	.align 32
_instrux_FLDCW:
	.long	168
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC428
	.long	8200
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC429:
	.ascii "\300\1\331\204\0"
	.data
	.align 32
_instrux_FLDENV:
	.long	169
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC429
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC430:
	.ascii "\2\331\352\0"
	.data
	.align 32
_instrux_FLDL2E:
	.long	170
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC430
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC431:
	.ascii "\2\331\351\0"
	.data
	.align 32
_instrux_FLDL2T:
	.long	171
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC431
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC432:
	.ascii "\2\331\354\0"
	.data
	.align 32
_instrux_FLDLG2:
	.long	172
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC432
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC433:
	.ascii "\2\331\355\0"
	.data
	.align 32
_instrux_FLDLN2:
	.long	173
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC433
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC434:
	.ascii "\2\331\353\0"
	.data
	.align 32
_instrux_FLDPI:
	.long	174
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC434
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC435:
	.ascii "\2\331\356\0"
	.data
	.align 32
_instrux_FLDZ:
	.long	175
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC435
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC436:
	.ascii "\300\1\330\201\0"
LC437:
	.ascii "\300\1\334\201\0"
LC438:
	.ascii "\1\334\10\310\0"
LC439:
	.ascii "\1\330\10\310\0"
LC440:
	.ascii "\1\330\11\310\0"
	.data
	.align 32
_instrux_FMUL:
	.long	176
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC436
	.long	8192
	.long	176
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC437
	.long	8192
	.long	176
	.long	1
	.long	16777472
	.long	0
	.long	0
	.long	LC438
	.long	8192
	.long	176
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC438
	.long	8192
	.long	176
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC439
	.long	8192
	.long	176
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC440
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC441:
	.ascii "\1\336\10\310\0"
	.data
	.align 32
_instrux_FMULP:
	.long	177
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC441
	.long	8192
	.long	177
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC441
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC442:
	.ascii "\2\333\342\0"
	.data
	.align 32
_instrux_FNCLEX:
	.long	178
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC442
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC443:
	.ascii "\2\333\341\0"
	.data
	.align 32
_instrux_FNDISI:
	.long	179
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC443
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC444:
	.ascii "\2\333\340\0"
	.data
	.align 32
_instrux_FNENI:
	.long	180
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC444
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC445:
	.ascii "\2\333\343\0"
	.data
	.align 32
_instrux_FNINIT:
	.long	181
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC445
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC446:
	.ascii "\2\331\320\0"
	.data
	.align 32
_instrux_FNOP:
	.long	182
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC446
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC447:
	.ascii "\300\1\335\206\0"
	.data
	.align 32
_instrux_FNSAVE:
	.long	183
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC447
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC448:
	.ascii "\300\1\331\207\0"
	.data
	.align 32
_instrux_FNSTCW:
	.long	184
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC448
	.long	8200
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC449:
	.ascii "\300\1\331\206\0"
	.data
	.align 32
_instrux_FNSTENV:
	.long	185
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC449
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC450:
	.ascii "\300\1\335\207\0"
LC451:
	.ascii "\2\337\340\0"
	.data
	.align 32
_instrux_FNSTSW:
	.long	186
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC450
	.long	8200
	.long	186
	.long	1
	.long	2166786
	.long	0
	.long	0
	.long	LC451
	.long	33562624
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC452:
	.ascii "\2\331\363\0"
	.data
	.align 32
_instrux_FPATAN:
	.long	187
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC452
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC453:
	.ascii "\2\331\370\0"
	.data
	.align 32
_instrux_FPREM:
	.long	188
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC453
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC454:
	.ascii "\2\331\365\0"
	.data
	.align 32
_instrux_FPREM1:
	.long	189
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC454
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC455:
	.ascii "\2\331\362\0"
	.data
	.align 32
_instrux_FPTAN:
	.long	190
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC455
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC456:
	.ascii "\2\331\374\0"
	.data
	.align 32
_instrux_FRNDINT:
	.long	191
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC456
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC457:
	.ascii "\300\1\335\204\0"
	.data
	.align 32
_instrux_FRSTOR:
	.long	192
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC457
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC458:
	.ascii "\300\2\233\335\206\0"
	.data
	.align 32
_instrux_FSAVE:
	.long	193
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC458
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC459:
	.ascii "\2\331\375\0"
	.data
	.align 32
_instrux_FSCALE:
	.long	194
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC459
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC460:
	.ascii "\2\333\344\0"
	.data
	.align 32
_instrux_FSETPM:
	.long	195
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC460
	.long	33562624
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC461:
	.ascii "\2\331\376\0"
	.data
	.align 32
_instrux_FSIN:
	.long	196
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC461
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC462:
	.ascii "\2\331\373\0"
	.data
	.align 32
_instrux_FSINCOS:
	.long	197
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC462
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC463:
	.ascii "\2\331\372\0"
	.data
	.align 32
_instrux_FSQRT:
	.long	198
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC463
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC464:
	.ascii "\300\1\331\202\0"
LC465:
	.ascii "\300\1\335\202\0"
LC466:
	.ascii "\1\335\10\320\0"
	.data
	.align 32
_instrux_FST:
	.long	199
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC464
	.long	8192
	.long	199
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC465
	.long	8192
	.long	199
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC466
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC467:
	.ascii "\300\2\233\331\207\0"
	.data
	.align 32
_instrux_FSTCW:
	.long	200
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC467
	.long	8200
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC468:
	.ascii "\300\2\233\331\206\0"
	.data
	.align 32
_instrux_FSTENV:
	.long	201
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC468
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC469:
	.ascii "\300\1\331\203\0"
LC470:
	.ascii "\300\1\335\203\0"
LC471:
	.ascii "\300\1\333\207\0"
LC472:
	.ascii "\1\335\10\330\0"
	.data
	.align 32
_instrux_FSTP:
	.long	202
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC469
	.long	8192
	.long	202
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC470
	.long	8192
	.long	202
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC471
	.long	8192
	.long	202
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC472
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC473:
	.ascii "\300\2\233\335\207\0"
LC474:
	.ascii "\3\233\337\340\0"
	.data
	.align 32
_instrux_FSTSW:
	.long	203
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC473
	.long	8200
	.long	203
	.long	1
	.long	2166786
	.long	0
	.long	0
	.long	LC474
	.long	33562624
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC475:
	.ascii "\300\1\330\204\0"
LC476:
	.ascii "\300\1\334\204\0"
LC477:
	.ascii "\1\334\10\350\0"
LC478:
	.ascii "\1\330\10\340\0"
LC479:
	.ascii "\1\330\11\340\0"
	.data
	.align 32
_instrux_FSUB:
	.long	204
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC475
	.long	8192
	.long	204
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC476
	.long	8192
	.long	204
	.long	1
	.long	16777472
	.long	0
	.long	0
	.long	LC477
	.long	8192
	.long	204
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC477
	.long	8192
	.long	204
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC478
	.long	8192
	.long	204
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC479
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC480:
	.ascii "\1\336\10\350\0"
	.data
	.align 32
_instrux_FSUBP:
	.long	205
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC480
	.long	8192
	.long	205
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC480
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC481:
	.ascii "\300\1\330\205\0"
LC482:
	.ascii "\300\1\334\205\0"
LC483:
	.ascii "\1\334\10\340\0"
LC484:
	.ascii "\1\330\10\350\0"
LC485:
	.ascii "\1\330\11\350\0"
	.data
	.align 32
_instrux_FSUBR:
	.long	206
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC481
	.long	8192
	.long	206
	.long	1
	.long	2113544
	.long	0
	.long	0
	.long	LC482
	.long	8192
	.long	206
	.long	1
	.long	16777472
	.long	0
	.long	0
	.long	LC483
	.long	8192
	.long	206
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC483
	.long	8192
	.long	206
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC484
	.long	8192
	.long	206
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC485
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC486:
	.ascii "\1\336\10\340\0"
	.data
	.align 32
_instrux_FSUBRP:
	.long	207
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC486
	.long	8192
	.long	207
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC486
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC487:
	.ascii "\2\331\344\0"
	.data
	.align 32
_instrux_FTST:
	.long	208
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC487
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC488:
	.ascii "\1\335\10\340\0"
LC489:
	.ascii "\1\335\11\340\0"
	.data
	.align 32
_instrux_FUCOM:
	.long	209
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC488
	.long	50339840
	.long	209
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC489
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC490:
	.ascii "\1\333\10\350\0"
LC491:
	.ascii "\1\333\11\350\0"
	.data
	.align 32
_instrux_FUCOMI:
	.long	210
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC490
	.long	100671488
	.long	210
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC491
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC492:
	.ascii "\1\337\10\350\0"
LC493:
	.ascii "\1\337\11\350\0"
	.data
	.align 32
_instrux_FUCOMIP:
	.long	211
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC492
	.long	100671488
	.long	211
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC493
	.long	100671488
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC494:
	.ascii "\1\335\10\350\0"
LC495:
	.ascii "\1\335\11\350\0"
	.data
	.align 32
_instrux_FUCOMP:
	.long	212
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC494
	.long	50339840
	.long	212
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC495
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC496:
	.ascii "\2\332\351\0"
	.data
	.align 32
_instrux_FUCOMPP:
	.long	213
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC496
	.long	50339840
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC497:
	.ascii "\1\233\0"
	.data
	.align 32
_instrux_FWAIT:
	.long	214
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC497
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC498:
	.ascii "\2\331\345\0"
	.data
	.align 32
_instrux_FXAM:
	.long	215
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC498
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC499:
	.ascii "\2\331\311\0"
LC500:
	.ascii "\1\331\10\310\0"
LC501:
	.ascii "\1\331\11\310\0"
	.data
	.align 32
_instrux_FXCH:
	.long	216
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC499
	.long	8192
	.long	216
	.long	1
	.long	16777216
	.long	0
	.long	0
	.long	LC500
	.long	8192
	.long	216
	.long	2
	.long	16777216
	.long	16779264
	.long	0
	.long	LC500
	.long	8192
	.long	216
	.long	2
	.long	16779264
	.long	16777216
	.long	0
	.long	LC501
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC502:
	.ascii "\300\2\17\256\201\0"
	.data
	.align 32
_instrux_FXRSTOR:
	.long	217
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC502
	.long	100737024
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC503:
	.ascii "\300\2\17\256\200\0"
	.data
	.align 32
_instrux_FXSAVE:
	.long	218
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC503
	.long	100737024
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC504:
	.ascii "\2\331\364\0"
	.data
	.align 32
_instrux_FXTRACT:
	.long	219
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC504
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC505:
	.ascii "\2\331\361\0"
	.data
	.align 32
_instrux_FYL2X:
	.long	220
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC505
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC506:
	.ascii "\2\331\371\0"
	.data
	.align 32
_instrux_FYL2XP1:
	.long	221
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC506
	.long	8192
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC507:
	.ascii "\301\3f\17|H\0"
LC508:
	.ascii "\3f\17|H\0"
	.data
	.align 32
_instrux_HADDPD:
	.long	222
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC507
	.long	151257089
	.long	222
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC508
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC509:
	.ascii "\301\3\362\17|H\0"
LC510:
	.ascii "\3\362\17|H\0"
	.data
	.align 32
_instrux_HADDPS:
	.long	223
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC509
	.long	151257089
	.long	223
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC510
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC511:
	.ascii "\1\364\0"
	.data
	.align 32
_instrux_HLT:
	.long	224
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC511
	.long	256
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC512:
	.ascii "\301\3f\17}H\0"
LC513:
	.ascii "\3f\17}H\0"
	.data
	.align 32
_instrux_HSUBPD:
	.long	225
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC512
	.long	151257089
	.long	225
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC513
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC514:
	.ascii "\301\3\362\17}H\0"
LC515:
	.ascii "\3\362\17}H\0"
	.data
	.align 32
_instrux_HSUBPS:
	.long	226
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC514
	.long	151257089
	.long	226
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC515
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_IBTS:
	.long	227
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC257
	.long	50335752
	.long	227
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC258
	.long	50335744
	.long	227
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC259
	.long	50335760
	.long	227
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC260
	.long	50335744
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC516:
	.ascii "\1\361\0"
	.data
	.align 32
_instrux_ICEBP:
	.long	228
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC516
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC517:
	.ascii "\300\1\366\207\0"
LC518:
	.ascii "\320\300\1\367\207\0"
LC519:
	.ascii "\321\300\1\367\207\0"
	.data
	.align 32
_instrux_IDIV:
	.long	229
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC517
	.long	0
	.long	229
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC518
	.long	0
	.long	229
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC519
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC520:
	.ascii "\300\1\366\205\0"
LC521:
	.ascii "\320\300\1\367\205\0"
LC522:
	.ascii "\321\300\1\367\205\0"
LC523:
	.ascii "\320\301\2\17\257H\0"
LC524:
	.ascii "\320\2\17\257H\0"
LC525:
	.ascii "\321\301\2\17\257H\0"
LC526:
	.ascii "\321\2\17\257H\0"
LC527:
	.ascii "\320\301\1kH\16\0"
LC528:
	.ascii "\320\301\1iH\32\0"
LC529:
	.ascii "\320\301]\1iHZ\0"
LC530:
	.ascii "\320\1kH\16\0"
LC531:
	.ascii "\320\1iH\32\0"
LC532:
	.ascii "\320]\1iHZ\0"
LC533:
	.ascii "\321\301\1kH\16\0"
LC534:
	.ascii "\321\301\1iH\"\0"
LC535:
	.ascii "\321\301e\1iHb\0"
LC536:
	.ascii "\321\1kH\16\0"
LC537:
	.ascii "\321\1iH\"\0"
LC538:
	.ascii "\321e\1iHb\0"
LC539:
	.ascii "\320\1k@\15\0"
LC540:
	.ascii "\320\1i@\31\0"
LC541:
	.ascii "\320\\\1i@Y\0"
LC542:
	.ascii "\321\1k@\15\0"
LC543:
	.ascii "\321\1i@!\0"
LC544:
	.ascii "\321d\1i@a\0"
	.data
	.align 32
_instrux_IMUL:
	.long	230
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC520
	.long	0
	.long	230
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC521
	.long	0
	.long	230
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC522
	.long	50331648
	.long	230
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC523
	.long	50331649
	.long	230
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC524
	.long	50331648
	.long	230
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC525
	.long	50331649
	.long	230
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC526
	.long	50331648
	.long	230
	.long	3
	.long	2101250
	.long	2113536
	.long	8193
	.long	LC527
	.long	16777217
	.long	230
	.long	3
	.long	2101250
	.long	2113536
	.long	1073750016
	.long	LC527
	.long	16777217
	.long	230
	.long	3
	.long	2101250
	.long	2113536
	.long	8194
	.long	LC528
	.long	16777217
	.long	230
	.long	3
	.long	2101250
	.long	2113536
	.long	8192
	.long	LC529
	.long	16777217
	.long	230
	.long	3
	.long	2101250
	.long	2101250
	.long	8193
	.long	LC530
	.long	16777216
	.long	230
	.long	3
	.long	2101250
	.long	2101250
	.long	1073750016
	.long	LC530
	.long	16777217
	.long	230
	.long	3
	.long	2101250
	.long	2101250
	.long	8194
	.long	LC531
	.long	16777216
	.long	230
	.long	3
	.long	2101250
	.long	2101250
	.long	8192
	.long	LC532
	.long	16777217
	.long	230
	.long	3
	.long	2101252
	.long	2113536
	.long	8193
	.long	LC533
	.long	50331649
	.long	230
	.long	3
	.long	2101252
	.long	2113536
	.long	1073750016
	.long	LC533
	.long	50331649
	.long	230
	.long	3
	.long	2101252
	.long	2113536
	.long	8196
	.long	LC534
	.long	50331649
	.long	230
	.long	3
	.long	2101252
	.long	2113536
	.long	8192
	.long	LC535
	.long	50331649
	.long	230
	.long	3
	.long	2101252
	.long	2101252
	.long	8193
	.long	LC536
	.long	50331648
	.long	230
	.long	3
	.long	2101252
	.long	2101252
	.long	1073750016
	.long	LC536
	.long	50331649
	.long	230
	.long	3
	.long	2101252
	.long	2101252
	.long	8196
	.long	LC537
	.long	50331648
	.long	230
	.long	3
	.long	2101252
	.long	2101252
	.long	8192
	.long	LC538
	.long	50331649
	.long	230
	.long	2
	.long	2101250
	.long	8193
	.long	0
	.long	LC539
	.long	16777216
	.long	230
	.long	2
	.long	2101250
	.long	1073750016
	.long	0
	.long	LC539
	.long	16777217
	.long	230
	.long	2
	.long	2101250
	.long	8194
	.long	0
	.long	LC540
	.long	16777216
	.long	230
	.long	2
	.long	2101250
	.long	8192
	.long	0
	.long	LC541
	.long	16777217
	.long	230
	.long	2
	.long	2101252
	.long	8193
	.long	0
	.long	LC542
	.long	50331648
	.long	230
	.long	2
	.long	2101252
	.long	1073750016
	.long	0
	.long	LC542
	.long	50331649
	.long	230
	.long	2
	.long	2101252
	.long	8196
	.long	0
	.long	LC543
	.long	50331648
	.long	230
	.long	2
	.long	2101252
	.long	8192
	.long	0
	.long	LC544
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC545:
	.ascii "\1\344\25\0"
LC546:
	.ascii "\320\1\345\25\0"
LC547:
	.ascii "\321\1\345\25\0"
LC548:
	.ascii "\1\354\0"
LC549:
	.ascii "\320\1\355\0"
LC550:
	.ascii "\321\1\355\0"
	.data
	.align 32
_instrux_IN:
	.long	231
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC545
	.long	4
	.long	231
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC546
	.long	4
	.long	231
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC547
	.long	50331652
	.long	231
	.long	2
	.long	2166785
	.long	2363394
	.long	0
	.long	LC548
	.long	0
	.long	231
	.long	2
	.long	2166786
	.long	2363394
	.long	0
	.long	LC549
	.long	0
	.long	231
	.long	2
	.long	2166788
	.long	2363394
	.long	0
	.long	LC550
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC551:
	.ascii "\320\10@\0"
LC552:
	.ascii "\321\10@\0"
LC553:
	.ascii "\300\1\376\200\0"
LC554:
	.ascii "\320\300\1\377\200\0"
LC555:
	.ascii "\321\300\1\377\200\0"
	.data
	.align 32
_instrux_INC:
	.long	232
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC551
	.long	0
	.long	232
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC552
	.long	50331648
	.long	232
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC553
	.long	0
	.long	232
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC554
	.long	0
	.long	232
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC555
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_INCBIN:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC556:
	.ascii "\1l\0"
	.data
	.align 32
_instrux_INSB:
	.long	234
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC556
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC557:
	.ascii "\321\1m\0"
	.data
	.align 32
_instrux_INSD:
	.long	235
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC557
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC558:
	.ascii "\320\1m\0"
	.data
	.align 32
_instrux_INSW:
	.long	236
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC558
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC559:
	.ascii "\1\315\24\0"
	.data
	.align 32
_instrux_INT:
	.long	237
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC559
	.long	4
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_INT01:
	.long	238
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC516
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC560:
	.ascii "\1\314\0"
	.data
	.align 32
_instrux_INT03:
	.long	239
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC560
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_INT1:
	.long	240
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC516
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_INT3:
	.long	241
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC560
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC561:
	.ascii "\1\316\0"
	.data
	.align 32
_instrux_INTO:
	.long	242
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC561
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC562:
	.ascii "\2\17\10\0"
	.data
	.align 32
_instrux_INVD:
	.long	243
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC562
	.long	67109120
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC563:
	.ascii "\300\2\17\1\207\0"
	.data
	.align 32
_instrux_INVLPG:
	.long	244
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC563
	.long	67109120
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC564:
	.ascii "\322\1\317\0"
	.data
	.align 32
_instrux_IRET:
	.long	245
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC564
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC565:
	.ascii "\321\1\317\0"
	.data
	.align 32
_instrux_IRETD:
	.long	246
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC565
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC566:
	.ascii "\320\1\317\0"
	.data
	.align 32
_instrux_IRETW:
	.long	247
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC566
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC567:
	.ascii "\310\1\343(\0"
	.data
	.align 32
_instrux_JCXZ:
	.long	248
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC567
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC568:
	.ascii "\311\1\343(\0"
	.data
	.align 32
_instrux_JECXZ:
	.long	249
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC568
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC569:
	.ascii "\1\353(\0"
LC570:
	.ascii "\371\1\353(\0"
LC571:
	.ascii "\322\1\351"
	.ascii "4\0"
LC572:
	.ascii "\322\1\352\34\37\0"
LC573:
	.ascii "\320\1\351"
	.ascii "4\0"
LC574:
	.ascii "\320\1\352\34\37\0"
LC575:
	.ascii "\321\1\351"
	.ascii "4\0"
LC576:
	.ascii "\321\1\352\34\37\0"
LC577:
	.ascii "\322\1\352\35\30\0"
LC578:
	.ascii "\320\1\352\31\30\0"
LC579:
	.ascii "\321\1\352!\30\0"
LC580:
	.ascii "\322\300\1\377\205\0"
LC581:
	.ascii "\320\300\1\377\205\0"
LC582:
	.ascii "\321\300\1\377\205\0"
LC583:
	.ascii "\322\300\1\377\204\0"
LC584:
	.ascii "\320\300\1\377\204\0"
LC585:
	.ascii "\321\300\1\377\204\0"
	.data
	.align 32
_instrux_JMP:
	.long	250
	.long	1
	.long	8320
	.long	0
	.long	0
	.long	LC569
	.long	0
	.long	250
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC570
	.long	0
	.long	250
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC571
	.long	0
	.long	250
	.long	1
	.long	8256
	.long	0
	.long	0
	.long	LC571
	.long	0
	.long	250
	.long	1
	.long	8224
	.long	0
	.long	0
	.long	LC572
	.long	0
	.long	250
	.long	1
	.long	8194
	.long	0
	.long	0
	.long	LC573
	.long	0
	.long	250
	.long	1
	.long	8258
	.long	0
	.long	0
	.long	LC573
	.long	0
	.long	250
	.long	1
	.long	8226
	.long	0
	.long	0
	.long	LC574
	.long	0
	.long	250
	.long	1
	.long	8196
	.long	0
	.long	0
	.long	LC575
	.long	50331648
	.long	250
	.long	1
	.long	8260
	.long	0
	.long	0
	.long	LC575
	.long	50331648
	.long	250
	.long	1
	.long	8228
	.long	0
	.long	0
	.long	LC576
	.long	50331648
	.long	250
	.long	2
	.long	8704
	.long	8192
	.long	0
	.long	LC577
	.long	0
	.long	250
	.long	2
	.long	8706
	.long	8192
	.long	0
	.long	LC578
	.long	0
	.long	250
	.long	2
	.long	8704
	.long	8194
	.long	0
	.long	LC578
	.long	0
	.long	250
	.long	2
	.long	8708
	.long	8192
	.long	0
	.long	LC579
	.long	50331648
	.long	250
	.long	2
	.long	8704
	.long	8196
	.long	0
	.long	LC579
	.long	50331648
	.long	250
	.long	1
	.long	2113568
	.long	0
	.long	0
	.long	LC580
	.long	0
	.long	250
	.long	1
	.long	2113570
	.long	0
	.long	0
	.long	LC581
	.long	0
	.long	250
	.long	1
	.long	2113572
	.long	0
	.long	0
	.long	LC582
	.long	50331648
	.long	250
	.long	1
	.long	2113600
	.long	0
	.long	0
	.long	LC583
	.long	0
	.long	250
	.long	1
	.long	2113602
	.long	0
	.long	0
	.long	LC584
	.long	0
	.long	250
	.long	1
	.long	2113604
	.long	0
	.long	0
	.long	LC585
	.long	50331648
	.long	250
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC584
	.long	0
	.long	250
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC585
	.long	50331648
	.long	250
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC583
	.long	0
	.long	250
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC584
	.long	0
	.long	250
	.long	1
	.long	2113540
	.long	0
	.long	0
	.long	LC585
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC586:
	.ascii "\322\2\17\270"
	.ascii "4\0"
LC587:
	.ascii "\320\2\17\270"
	.ascii "4\0"
LC588:
	.ascii "\321\2\17\270"
	.ascii "4\0"
LC589:
	.ascii "\320\2\17\0\206\0"
LC590:
	.ascii "\321\2\17\0\206\0"
	.data
	.align 32
_instrux_JMPE:
	.long	251
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC586
	.long	251658240
	.long	251
	.long	1
	.long	8194
	.long	0
	.long	0
	.long	LC587
	.long	251658240
	.long	251
	.long	1
	.long	8196
	.long	0
	.long	0
	.long	LC588
	.long	251658240
	.long	251
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC589
	.long	251658240
	.long	251
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC590
	.long	251658240
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC591:
	.ascii "\1\237\0"
	.data
	.align 32
_instrux_LAHF:
	.long	252
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC591
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC592:
	.ascii "\320\301\2\17\2H\0"
LC593:
	.ascii "\320\2\17\2H\0"
LC594:
	.ascii "\321\301\2\17\2H\0"
LC595:
	.ascii "\321\2\17\2H\0"
	.data
	.align 32
_instrux_LAR:
	.long	253
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC592
	.long	33555457
	.long	253
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC593
	.long	33555456
	.long	253
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC594
	.long	50332673
	.long	253
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC595
	.long	50332672
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC596:
	.ascii "\3\362\17\360H\0"
	.data
	.align 32
_instrux_LDDQU:
	.long	254
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC596
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC597:
	.ascii "\300\2\17\256\202\0"
	.data
	.align 32
_instrux_LDMXCSR:
	.long	255
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC597
	.long	117506064
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC598:
	.ascii "\320\301\1\305H\0"
LC599:
	.ascii "\321\301\1\305H\0"
	.data
	.align 32
_instrux_LDS:
	.long	256
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC598
	.long	0
	.long	256
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC599
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC600:
	.ascii "\320\301\1\215H\0"
LC601:
	.ascii "\321\301\1\215H\0"
	.data
	.align 32
_instrux_LEA:
	.long	257
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC600
	.long	0
	.long	257
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC601
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC602:
	.ascii "\1\311\0"
	.data
	.align 32
_instrux_LEAVE:
	.long	258
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC602
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC603:
	.ascii "\320\301\1\304H\0"
LC604:
	.ascii "\321\301\1\304H\0"
	.data
	.align 32
_instrux_LES:
	.long	259
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC603
	.long	0
	.long	259
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC604
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC605:
	.ascii "\3\17\256\350\0"
	.data
	.align 32
_instrux_LFENCE:
	.long	260
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC605
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC606:
	.ascii "\320\301\2\17\264H\0"
LC607:
	.ascii "\321\301\2\17\264H\0"
	.data
	.align 32
_instrux_LFS:
	.long	261
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC606
	.long	50331648
	.long	261
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC607
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC608:
	.ascii "\300\2\17\1\202\0"
	.data
	.align 32
_instrux_LGDT:
	.long	262
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC608
	.long	33554688
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC609:
	.ascii "\320\301\2\17\265H\0"
LC610:
	.ascii "\321\301\2\17\265H\0"
	.data
	.align 32
_instrux_LGS:
	.long	263
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC609
	.long	50331648
	.long	263
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC610
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC611:
	.ascii "\300\2\17\1\203\0"
	.data
	.align 32
_instrux_LIDT:
	.long	264
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC611
	.long	33554688
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC612:
	.ascii "\300\1\17\17\202\0"
LC613:
	.ascii "\1\17\17\202\0"
	.data
	.align 32
_instrux_LLDT:
	.long	265
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC612
	.long	33555712
	.long	265
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC612
	.long	33555712
	.long	265
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC613
	.long	33555712
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC614:
	.ascii "\300\2\17\1\206\0"
LC615:
	.ascii "\2\17\1\206\0"
	.data
	.align 32
_instrux_LMSW:
	.long	266
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC614
	.long	33554688
	.long	266
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC614
	.long	33554688
	.long	266
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC615
	.long	33554688
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC616:
	.ascii "\2\17\7\0"
	.data
	.align 32
_instrux_LOADALL:
	.long	267
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC616
	.long	50335744
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC617:
	.ascii "\2\17\5\0"
	.data
	.align 32
_instrux_LOADALL286:
	.long	268
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC617
	.long	33558528
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC618:
	.ascii "\1\254\0"
	.data
	.align 32
_instrux_LODSB:
	.long	269
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC618
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC619:
	.ascii "\321\1\255\0"
	.data
	.align 32
_instrux_LODSD:
	.long	270
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC619
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC620:
	.ascii "\320\1\255\0"
	.data
	.align 32
_instrux_LODSW:
	.long	271
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC620
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC621:
	.ascii "\312\1\342(\0"
LC622:
	.ascii "\310\1\342(\0"
LC623:
	.ascii "\311\1\342(\0"
	.data
	.align 32
_instrux_LOOP:
	.long	272
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC621
	.long	0
	.long	272
	.long	2
	.long	8192
	.long	2232322
	.long	0
	.long	LC622
	.long	0
	.long	272
	.long	2
	.long	8192
	.long	2232324
	.long	0
	.long	LC623
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC624:
	.ascii "\312\1\341(\0"
LC625:
	.ascii "\310\1\341(\0"
LC626:
	.ascii "\311\1\341(\0"
	.data
	.align 32
_instrux_LOOPE:
	.long	273
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC624
	.long	0
	.long	273
	.long	2
	.long	8192
	.long	2232322
	.long	0
	.long	LC625
	.long	0
	.long	273
	.long	2
	.long	8192
	.long	2232324
	.long	0
	.long	LC626
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC627:
	.ascii "\312\1\340(\0"
LC628:
	.ascii "\310\1\340(\0"
LC629:
	.ascii "\311\1\340(\0"
	.data
	.align 32
_instrux_LOOPNE:
	.long	274
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC627
	.long	0
	.long	274
	.long	2
	.long	8192
	.long	2232322
	.long	0
	.long	LC628
	.long	0
	.long	274
	.long	2
	.long	8192
	.long	2232324
	.long	0
	.long	LC629
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_LOOPNZ:
	.long	275
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC627
	.long	0
	.long	275
	.long	2
	.long	8192
	.long	2232322
	.long	0
	.long	LC628
	.long	0
	.long	275
	.long	2
	.long	8192
	.long	2232324
	.long	0
	.long	LC629
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_LOOPZ:
	.long	276
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC624
	.long	0
	.long	276
	.long	2
	.long	8192
	.long	2232322
	.long	0
	.long	LC625
	.long	0
	.long	276
	.long	2
	.long	8192
	.long	2232324
	.long	0
	.long	LC626
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC630:
	.ascii "\320\301\2\17\3H\0"
LC631:
	.ascii "\320\2\17\3H\0"
LC632:
	.ascii "\321\301\2\17\3H\0"
LC633:
	.ascii "\321\2\17\3H\0"
	.data
	.align 32
_instrux_LSL:
	.long	277
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC630
	.long	33555457
	.long	277
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC631
	.long	33555456
	.long	277
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC632
	.long	50332673
	.long	277
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC633
	.long	50332672
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC634:
	.ascii "\320\301\2\17\262H\0"
LC635:
	.ascii "\321\301\2\17\262H\0"
	.data
	.align 32
_instrux_LSS:
	.long	278
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC634
	.long	50331648
	.long	278
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC635
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC636:
	.ascii "\300\1\17\17\203\0"
LC637:
	.ascii "\1\17\17\203\0"
	.data
	.align 32
_instrux_LTR:
	.long	279
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC636
	.long	33555712
	.long	279
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC636
	.long	33555712
	.long	279
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC637
	.long	33555712
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC638:
	.ascii "\3f\17\367H\0"
	.data
	.align 32
_instrux_MASKMOVDQU:
	.long	280
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC638
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC639:
	.ascii "\2\17\367H\0"
	.data
	.align 32
_instrux_MASKMOVQ:
	.long	281
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC639
	.long	117456896
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC640:
	.ascii "\3f\17_H\0"
LC641:
	.ascii "\301\3f\17_H\0"
	.data
	.align 32
_instrux_MAXPD:
	.long	282
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC640
	.long	134348800
	.long	282
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC641
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC642:
	.ascii "\301\331\2\17_H\0"
LC643:
	.ascii "\331\2\17_H\0"
	.data
	.align 32
_instrux_MAXPS:
	.long	283
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC642
	.long	117506048
	.long	283
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC643
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC644:
	.ascii "\3\362\17_H\0"
LC645:
	.ascii "\301\3\362\17_H\0"
	.data
	.align 32
_instrux_MAXSD:
	.long	284
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC644
	.long	134348800
	.long	284
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC645
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC646:
	.ascii "\301\333\2\17_H\0"
LC647:
	.ascii "\333\2\17_H\0"
	.data
	.align 32
_instrux_MAXSS:
	.long	285
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC646
	.long	117506048
	.long	285
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC647
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC648:
	.ascii "\3\17\256\360\0"
	.data
	.align 32
_instrux_MFENCE:
	.long	286
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC648
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC649:
	.ascii "\3f\17]H\0"
LC650:
	.ascii "\301\3f\17]H\0"
	.data
	.align 32
_instrux_MINPD:
	.long	287
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC649
	.long	134348800
	.long	287
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC650
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC651:
	.ascii "\301\331\2\17]H\0"
LC652:
	.ascii "\331\2\17]H\0"
	.data
	.align 32
_instrux_MINPS:
	.long	288
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC651
	.long	117506048
	.long	288
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC652
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC653:
	.ascii "\3\362\17]H\0"
LC654:
	.ascii "\301\3\362\17]H\0"
	.data
	.align 32
_instrux_MINSD:
	.long	289
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC653
	.long	134348800
	.long	289
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC654
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC655:
	.ascii "\301\333\2\17]H\0"
LC656:
	.ascii "\333\2\17]H\0"
	.data
	.align 32
_instrux_MINSS:
	.long	290
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC655
	.long	117506048
	.long	290
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC656
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC657:
	.ascii "\3\17\1\310\0"
	.data
	.align 32
_instrux_MONITOR:
	.long	291
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC657
	.long	150994944
	.long	291
	.long	3
	.long	2166788
	.long	2232324
	.long	2363396
	.long	LC657
	.long	150994944
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC658:
	.ascii "\300\1\214A\0"
LC659:
	.ascii "\320\1\214A\0"
LC660:
	.ascii "\321\1\214A\0"
LC661:
	.ascii "\301\1\216H\0"
LC662:
	.ascii "\1\216H\0"
LC663:
	.ascii "\301\1\240%\0"
LC664:
	.ascii "\301\320\1\241%\0"
LC665:
	.ascii "\301\321\1\241%\0"
LC666:
	.ascii "\300\1\242$\0"
LC667:
	.ascii "\300\320\1\243$\0"
LC668:
	.ascii "\300\321\1\243$\0"
LC669:
	.ascii "\2\17 A\0"
LC670:
	.ascii "\2\17!A\0"
LC671:
	.ascii "\2\17$A\0"
LC672:
	.ascii "\2\17\"H\0"
LC673:
	.ascii "\2\17#H\0"
LC674:
	.ascii "\2\17&H\0"
LC675:
	.ascii "\300\1\210A\0"
LC676:
	.ascii "\1\210A\0"
LC677:
	.ascii "\320\300\1\211A\0"
LC678:
	.ascii "\320\1\211A\0"
LC679:
	.ascii "\321\300\1\211A\0"
LC680:
	.ascii "\321\1\211A\0"
LC681:
	.ascii "\301\1\212H\0"
LC682:
	.ascii "\1\212H\0"
LC683:
	.ascii "\320\301\1\213H\0"
LC684:
	.ascii "\320\1\213H\0"
LC685:
	.ascii "\321\301\1\213H\0"
LC686:
	.ascii "\321\1\213H\0"
LC687:
	.ascii "\10\260\21\0"
LC688:
	.ascii "\320\10\270\31\0"
LC689:
	.ascii "\321\10\270!\0"
LC690:
	.ascii "\300\1\306\200\21\0"
LC691:
	.ascii "\320\300\1\307\200\31\0"
LC692:
	.ascii "\321\300\1\307\200!\0"
	.data
	.align 32
_instrux_MOV:
	.long	292
	.long	2
	.long	2113536
	.long	528386
	.long	0
	.long	LC658
	.long	1
	.long	292
	.long	2
	.long	2101250
	.long	528386
	.long	0
	.long	LC659
	.long	0
	.long	292
	.long	2
	.long	2101252
	.long	528386
	.long	0
	.long	LC660
	.long	50331648
	.long	292
	.long	2
	.long	528386
	.long	2113536
	.long	0
	.long	LC661
	.long	1
	.long	292
	.long	2
	.long	528386
	.long	2101250
	.long	0
	.long	LC662
	.long	0
	.long	292
	.long	2
	.long	528386
	.long	2101252
	.long	0
	.long	LC662
	.long	50331648
	.long	292
	.long	2
	.long	2166785
	.long	6307840
	.long	0
	.long	LC663
	.long	1
	.long	292
	.long	2
	.long	2166786
	.long	6307840
	.long	0
	.long	LC664
	.long	1
	.long	292
	.long	2
	.long	2166788
	.long	6307840
	.long	0
	.long	LC665
	.long	50331649
	.long	292
	.long	2
	.long	6307840
	.long	2166785
	.long	0
	.long	LC666
	.long	1
	.long	292
	.long	2
	.long	6307840
	.long	2166786
	.long	0
	.long	LC667
	.long	1
	.long	292
	.long	2
	.long	6307840
	.long	2166788
	.long	0
	.long	LC668
	.long	50331649
	.long	292
	.long	2
	.long	2101252
	.long	135270404
	.long	0
	.long	LC669
	.long	50331904
	.long	292
	.long	2
	.long	2101252
	.long	269488132
	.long	0
	.long	LC670
	.long	50331904
	.long	292
	.long	2
	.long	2101252
	.long	537923588
	.long	0
	.long	LC671
	.long	50331904
	.long	292
	.long	2
	.long	135270404
	.long	2101252
	.long	0
	.long	LC672
	.long	50331904
	.long	292
	.long	2
	.long	269488132
	.long	2101252
	.long	0
	.long	LC673
	.long	50331904
	.long	292
	.long	2
	.long	537923588
	.long	2101252
	.long	0
	.long	LC674
	.long	50331904
	.long	292
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC675
	.long	1
	.long	292
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC676
	.long	0
	.long	292
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC677
	.long	1
	.long	292
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC678
	.long	0
	.long	292
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC679
	.long	50331649
	.long	292
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC680
	.long	50331648
	.long	292
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC681
	.long	1
	.long	292
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC682
	.long	0
	.long	292
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC683
	.long	1
	.long	292
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC684
	.long	0
	.long	292
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC685
	.long	50331649
	.long	292
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC686
	.long	50331648
	.long	292
	.long	2
	.long	2101249
	.long	8192
	.long	0
	.long	LC687
	.long	1
	.long	292
	.long	2
	.long	2101250
	.long	8192
	.long	0
	.long	LC688
	.long	1
	.long	292
	.long	2
	.long	2101252
	.long	8192
	.long	0
	.long	LC689
	.long	50331649
	.long	292
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC690
	.long	1
	.long	292
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC691
	.long	1
	.long	292
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC692
	.long	50331649
	.long	292
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC690
	.long	1
	.long	292
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC691
	.long	1
	.long	292
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC692
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC693:
	.ascii "\3f\17(H\0"
LC694:
	.ascii "\3f\17)H\0"
LC695:
	.ascii "\300\3f\17)A\0"
LC696:
	.ascii "\301\3f\17(H\0"
	.data
	.align 32
_instrux_MOVAPD:
	.long	293
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC693
	.long	134348800
	.long	293
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC694
	.long	134348800
	.long	293
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC695
	.long	134348801
	.long	293
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC696
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC697:
	.ascii "\301\2\17(H\0"
LC698:
	.ascii "\300\2\17)A\0"
LC699:
	.ascii "\2\17(H\0"
LC700:
	.ascii "\2\17)A\0"
	.data
	.align 32
_instrux_MOVAPS:
	.long	294
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC697
	.long	117506048
	.long	294
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC698
	.long	117506048
	.long	294
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC699
	.long	117506048
	.long	294
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC700
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC701:
	.ascii "\301\2\17nH\0"
LC702:
	.ascii "\2\17nH\0"
LC703:
	.ascii "\300\2\17~A\0"
LC704:
	.ascii "\2\17~A\0"
LC705:
	.ascii "\3f\17nH\0"
LC706:
	.ascii "\3f\17~A\0"
LC707:
	.ascii "\300\3f\17~A\0"
LC708:
	.ascii "\301\3f\17nH\0"
	.data
	.align 32
_instrux_MOVD:
	.long	295
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC701
	.long	83902480
	.long	295
	.long	2
	.long	2101256
	.long	2101252
	.long	0
	.long	LC702
	.long	83902464
	.long	295
	.long	2
	.long	2113536
	.long	2101256
	.long	0
	.long	LC703
	.long	83902480
	.long	295
	.long	2
	.long	2101252
	.long	2101256
	.long	0
	.long	LC704
	.long	83902464
	.long	295
	.long	2
	.long	2101264
	.long	2101252
	.long	0
	.long	LC705
	.long	134348800
	.long	295
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC706
	.long	134348800
	.long	295
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC707
	.long	134348800
	.long	295
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC708
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC709:
	.ascii "\301\3\362\17\22H\0"
LC710:
	.ascii "\3\362\17\22H\0"
	.data
	.align 32
_instrux_MOVDDUP:
	.long	296
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC709
	.long	151257088
	.long	296
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC710
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC711:
	.ascii "\3\362\17\326H\0"
	.data
	.align 32
_instrux_MOVDQ2Q:
	.long	297
	.long	2
	.long	2101256
	.long	2101264
	.long	0
	.long	LC711
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC712:
	.ascii "\3f\17oH\0"
LC713:
	.ascii "\300\3f\17\177A\0"
LC714:
	.ascii "\301\3f\17oH\0"
LC715:
	.ascii "\3f\17\177H\0"
	.data
	.align 32
_instrux_MOVDQA:
	.long	298
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC712
	.long	134348800
	.long	298
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC713
	.long	134348801
	.long	298
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC714
	.long	134348801
	.long	298
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC715
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC716:
	.ascii "\333\2\17oH\0"
LC717:
	.ascii "\333\300\2\17\177A\0"
LC718:
	.ascii "\301\333\2\17oH\0"
LC719:
	.ascii "\333\2\17\177H\0"
	.data
	.align 32
_instrux_MOVDQU:
	.long	299
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC716
	.long	134348800
	.long	299
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC717
	.long	134348801
	.long	299
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC718
	.long	134348801
	.long	299
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC719
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC720:
	.ascii "\2\17\22H\0"
	.data
	.align 32
_instrux_MOVHLPS:
	.long	300
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC720
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC721:
	.ascii "\300\3f\17\27A\0"
LC722:
	.ascii "\301\3f\17\26H\0"
	.data
	.align 32
_instrux_MOVHPD:
	.long	301
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC721
	.long	134348800
	.long	301
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC722
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC723:
	.ascii "\301\2\17\26H\0"
LC724:
	.ascii "\300\2\17\27A\0"
	.data
	.align 32
_instrux_MOVHPS:
	.long	302
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC723
	.long	117506048
	.long	302
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC724
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC725:
	.ascii "\2\17\26H\0"
	.data
	.align 32
_instrux_MOVLHPS:
	.long	303
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC725
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC726:
	.ascii "\300\3f\17\23A\0"
LC727:
	.ascii "\301\3f\17\22H\0"
	.data
	.align 32
_instrux_MOVLPD:
	.long	304
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC726
	.long	134348800
	.long	304
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC727
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC728:
	.ascii "\301\2\17\22H\0"
LC729:
	.ascii "\300\2\17\23A\0"
	.data
	.align 32
_instrux_MOVLPS:
	.long	305
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC728
	.long	117506048
	.long	305
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC729
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC730:
	.ascii "\3f\17PH\0"
	.data
	.align 32
_instrux_MOVMSKPD:
	.long	306
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC730
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC731:
	.ascii "\2\17PH\0"
	.data
	.align 32
_instrux_MOVMSKPS:
	.long	307
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC731
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC732:
	.ascii "\300\3f\17\347A\0"
	.data
	.align 32
_instrux_MOVNTDQ:
	.long	308
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC732
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC733:
	.ascii "\300\2\17\303A\0"
	.data
	.align 32
_instrux_MOVNTI:
	.long	309
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC733
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC734:
	.ascii "\300\3f\17+A\0"
	.data
	.align 32
_instrux_MOVNTPD:
	.long	310
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC734
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC735:
	.ascii "\300\2\17+A\0"
	.data
	.align 32
_instrux_MOVNTPS:
	.long	311
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC735
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC736:
	.ascii "\300\2\17\347A\0"
	.data
	.align 32
_instrux_MOVNTQ:
	.long	312
	.long	2
	.long	2113536
	.long	2101256
	.long	0
	.long	LC736
	.long	117456897
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC737:
	.ascii "\301\2\17oH\0"
LC738:
	.ascii "\2\17oH\0"
LC739:
	.ascii "\300\2\17\177A\0"
LC740:
	.ascii "\2\17\177A\0"
LC741:
	.ascii "\333\2\17~H\0"
LC742:
	.ascii "\3f\17\326H\0"
LC743:
	.ascii "\300\3f\17\326A\0"
LC744:
	.ascii "\301\333\2\17~H\0"
	.data
	.align 32
_instrux_MOVQ:
	.long	313
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC737
	.long	83902465
	.long	313
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC738
	.long	83902464
	.long	313
	.long	2
	.long	2113536
	.long	2101256
	.long	0
	.long	LC739
	.long	83902465
	.long	313
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC740
	.long	83902464
	.long	313
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC741
	.long	134348800
	.long	313
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC742
	.long	134348800
	.long	313
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC743
	.long	134348800
	.long	313
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC744
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC745:
	.ascii "\333\2\17\326H\0"
	.data
	.align 32
_instrux_MOVQ2DQ:
	.long	314
	.long	2
	.long	2101264
	.long	2101256
	.long	0
	.long	LC745
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC746:
	.ascii "\1\244\0"
	.data
	.align 32
_instrux_MOVSB:
	.long	315
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC746
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC747:
	.ascii "\321\1\245\0"
LC748:
	.ascii "\3\362\17\20H\0"
LC749:
	.ascii "\3\362\17\21H\0"
LC750:
	.ascii "\300\3\362\17\21A\0"
LC751:
	.ascii "\301\3\362\17\20H\0"
	.data
	.align 32
_instrux_MOVSD:
	.long	316
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC747
	.long	50331648
	.long	316
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC748
	.long	134348800
	.long	316
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC749
	.long	134348800
	.long	316
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC750
	.long	134348800
	.long	316
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC751
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC752:
	.ascii "\301\3\363\17\26H\0"
LC753:
	.ascii "\3\363\17\26H\0"
	.data
	.align 32
_instrux_MOVSHDUP:
	.long	317
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC752
	.long	151257088
	.long	317
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC753
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC754:
	.ascii "\301\3\363\17\22H\0"
LC755:
	.ascii "\3\363\17\22H\0"
	.data
	.align 32
_instrux_MOVSLDUP:
	.long	318
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC754
	.long	151257088
	.long	318
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC755
	.long	151257088
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC756:
	.ascii "\301\333\2\17\20H\0"
LC757:
	.ascii "\300\333\2\17\21A\0"
LC758:
	.ascii "\333\2\17\20H\0"
LC759:
	.ascii "\333\2\17\21A\0"
	.data
	.align 32
_instrux_MOVSS:
	.long	319
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC756
	.long	117506048
	.long	319
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC757
	.long	117506048
	.long	319
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC758
	.long	117506048
	.long	319
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC759
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC760:
	.ascii "\320\1\245\0"
	.data
	.align 32
_instrux_MOVSW:
	.long	320
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC760
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC761:
	.ascii "\320\301\2\17\276H\0"
LC762:
	.ascii "\320\2\17\276H\0"
LC763:
	.ascii "\321\301\2\17\276H\0"
LC764:
	.ascii "\321\301\2\17\277H\0"
	.data
	.align 32
_instrux_MOVSX:
	.long	321
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC761
	.long	50331652
	.long	321
	.long	2
	.long	2101250
	.long	2101249
	.long	0
	.long	LC762
	.long	50331648
	.long	321
	.long	2
	.long	2101252
	.long	2097153
	.long	0
	.long	LC763
	.long	50331648
	.long	321
	.long	2
	.long	2101252
	.long	2097154
	.long	0
	.long	LC764
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC765:
	.ascii "\3f\17\20H\0"
LC766:
	.ascii "\3f\17\21H\0"
LC767:
	.ascii "\300\3f\17\21A\0"
LC768:
	.ascii "\301\3f\17\20H\0"
	.data
	.align 32
_instrux_MOVUPD:
	.long	322
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC765
	.long	134348800
	.long	322
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC766
	.long	134348800
	.long	322
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC767
	.long	134348801
	.long	322
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC768
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC769:
	.ascii "\301\331\2\17\20H\0"
LC770:
	.ascii "\300\331\2\17\21A\0"
LC771:
	.ascii "\331\2\17\20H\0"
LC772:
	.ascii "\331\2\17\21A\0"
	.data
	.align 32
_instrux_MOVUPS:
	.long	323
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC769
	.long	117506048
	.long	323
	.long	2
	.long	2113536
	.long	2101264
	.long	0
	.long	LC770
	.long	117506048
	.long	323
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC771
	.long	117506048
	.long	323
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC772
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC773:
	.ascii "\320\301\2\17\266H\0"
LC774:
	.ascii "\320\2\17\266H\0"
LC775:
	.ascii "\321\301\2\17\266H\0"
LC776:
	.ascii "\321\301\2\17\267H\0"
	.data
	.align 32
_instrux_MOVZX:
	.long	324
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC773
	.long	50331652
	.long	324
	.long	2
	.long	2101250
	.long	2101249
	.long	0
	.long	LC774
	.long	50331648
	.long	324
	.long	2
	.long	2101252
	.long	2097153
	.long	0
	.long	LC775
	.long	50331648
	.long	324
	.long	2
	.long	2101252
	.long	2097154
	.long	0
	.long	LC776
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC777:
	.ascii "\300\1\366\204\0"
LC778:
	.ascii "\320\300\1\367\204\0"
LC779:
	.ascii "\321\300\1\367\204\0"
	.data
	.align 32
_instrux_MUL:
	.long	325
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC777
	.long	0
	.long	325
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC778
	.long	0
	.long	325
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC779
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC780:
	.ascii "\3f\17YH\0"
LC781:
	.ascii "\301\3f\17YH\0"
	.data
	.align 32
_instrux_MULPD:
	.long	326
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC780
	.long	134348800
	.long	326
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC781
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC782:
	.ascii "\301\2\17YH\0"
LC783:
	.ascii "\2\17YH\0"
	.data
	.align 32
_instrux_MULPS:
	.long	327
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC782
	.long	117506048
	.long	327
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC783
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC784:
	.ascii "\3\362\17YH\0"
LC785:
	.ascii "\301\3\362\17YH\0"
	.data
	.align 32
_instrux_MULSD:
	.long	328
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC784
	.long	134348800
	.long	328
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC785
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC786:
	.ascii "\301\333\2\17YH\0"
LC787:
	.ascii "\333\2\17YH\0"
	.data
	.align 32
_instrux_MULSS:
	.long	329
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC786
	.long	117506048
	.long	329
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC787
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC788:
	.ascii "\3\17\1\311\0"
	.data
	.align 32
_instrux_MWAIT:
	.long	330
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC788
	.long	150994944
	.long	330
	.long	2
	.long	2166788
	.long	2232324
	.long	0
	.long	LC788
	.long	150994944
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC789:
	.ascii "\300\1\366\203\0"
LC790:
	.ascii "\320\300\1\367\203\0"
LC791:
	.ascii "\321\300\1\367\203\0"
	.data
	.align 32
_instrux_NEG:
	.long	331
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC789
	.long	0
	.long	331
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC790
	.long	0
	.long	331
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC791
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC792:
	.ascii "\1\220\0"
	.data
	.align 32
_instrux_NOP:
	.long	332
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC792
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC793:
	.ascii "\300\1\366\202\0"
LC794:
	.ascii "\320\300\1\367\202\0"
LC795:
	.ascii "\321\300\1\367\202\0"
	.data
	.align 32
_instrux_NOT:
	.long	333
	.long	1
	.long	2097153
	.long	0
	.long	0
	.long	LC793
	.long	0
	.long	333
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC794
	.long	0
	.long	333
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC795
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC796:
	.ascii "\300\1\10A\0"
LC797:
	.ascii "\1\10A\0"
LC798:
	.ascii "\320\300\1\11A\0"
LC799:
	.ascii "\320\1\11A\0"
LC800:
	.ascii "\321\300\1\11A\0"
LC801:
	.ascii "\321\1\11A\0"
LC802:
	.ascii "\301\1\12H\0"
LC803:
	.ascii "\1\12H\0"
LC804:
	.ascii "\320\301\1\13H\0"
LC805:
	.ascii "\320\1\13H\0"
LC806:
	.ascii "\321\301\1\13H\0"
LC807:
	.ascii "\321\1\13H\0"
LC808:
	.ascii "\320\300\1\203\201\15\0"
LC809:
	.ascii "\321\300\1\203\201\15\0"
LC810:
	.ascii "\1\14\21\0"
LC811:
	.ascii "\320\1\203\201\15\0"
LC812:
	.ascii "\320\1\15\31\0"
LC813:
	.ascii "\321\1\203\201\15\0"
LC814:
	.ascii "\321\1\15!\0"
LC815:
	.ascii "\300\1\200\201\21\0"
LC816:
	.ascii "\320\300\\\1\201\201Y\0"
LC817:
	.ascii "\321\300d\1\201\201a\0"
	.data
	.align 32
_instrux_OR:
	.long	334
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC796
	.long	1
	.long	334
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC797
	.long	0
	.long	334
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC798
	.long	1
	.long	334
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC799
	.long	0
	.long	334
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC800
	.long	50331649
	.long	334
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC801
	.long	50331648
	.long	334
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC802
	.long	1
	.long	334
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC803
	.long	0
	.long	334
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC804
	.long	1
	.long	334
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC805
	.long	0
	.long	334
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC806
	.long	50331649
	.long	334
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC807
	.long	50331648
	.long	334
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC808
	.long	0
	.long	334
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC809
	.long	50331648
	.long	334
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC810
	.long	1
	.long	334
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC811
	.long	1
	.long	334
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC812
	.long	1
	.long	334
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC813
	.long	50331649
	.long	334
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC814
	.long	50331649
	.long	334
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC815
	.long	1
	.long	334
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC816
	.long	1
	.long	334
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC817
	.long	50331649
	.long	334
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC815
	.long	1
	.long	334
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC816
	.long	1
	.long	334
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC817
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC818:
	.ascii "\301\3f\17VH\0"
LC819:
	.ascii "\3f\17VH\0"
	.data
	.align 32
_instrux_ORPD:
	.long	335
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC818
	.long	134348801
	.long	335
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC819
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC820:
	.ascii "\301\2\17VH\0"
LC821:
	.ascii "\2\17VH\0"
	.data
	.align 32
_instrux_ORPS:
	.long	336
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC820
	.long	117506048
	.long	336
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC821
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC822:
	.ascii "\1\346\24\0"
LC823:
	.ascii "\320\1\347\24\0"
LC824:
	.ascii "\321\1\347\24\0"
LC825:
	.ascii "\1\356\0"
LC826:
	.ascii "\320\1\357\0"
LC827:
	.ascii "\321\1\357\0"
	.data
	.align 32
_instrux_OUT:
	.long	337
	.long	2
	.long	8192
	.long	2166785
	.long	0
	.long	LC822
	.long	4
	.long	337
	.long	2
	.long	8192
	.long	2166786
	.long	0
	.long	LC823
	.long	4
	.long	337
	.long	2
	.long	8192
	.long	2166788
	.long	0
	.long	LC824
	.long	50331652
	.long	337
	.long	2
	.long	2363394
	.long	2166785
	.long	0
	.long	LC825
	.long	0
	.long	337
	.long	2
	.long	2363394
	.long	2166786
	.long	0
	.long	LC826
	.long	0
	.long	337
	.long	2
	.long	2363394
	.long	2166788
	.long	0
	.long	LC827
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC828:
	.ascii "\1n\0"
	.data
	.align 32
_instrux_OUTSB:
	.long	338
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC828
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC829:
	.ascii "\321\1o\0"
	.data
	.align 32
_instrux_OUTSD:
	.long	339
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC829
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC830:
	.ascii "\320\1o\0"
	.data
	.align 32
_instrux_OUTSW:
	.long	340
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC830
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC831:
	.ascii "\301\2\17kH\0"
LC832:
	.ascii "\2\17kH\0"
LC833:
	.ascii "\3f\17kH\0"
LC834:
	.ascii "\301\3f\17kH\0"
	.data
	.align 32
_instrux_PACKSSDW:
	.long	341
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC831
	.long	83902465
	.long	341
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC832
	.long	83902464
	.long	341
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC833
	.long	134348800
	.long	341
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC834
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC835:
	.ascii "\301\2\17cH\0"
LC836:
	.ascii "\2\17cH\0"
LC837:
	.ascii "\3f\17cH\0"
LC838:
	.ascii "\301\3f\17cH\0"
	.data
	.align 32
_instrux_PACKSSWB:
	.long	342
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC835
	.long	83902465
	.long	342
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC836
	.long	83902464
	.long	342
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC837
	.long	134348800
	.long	342
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC838
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC839:
	.ascii "\301\2\17gH\0"
LC840:
	.ascii "\2\17gH\0"
LC841:
	.ascii "\3f\17gH\0"
LC842:
	.ascii "\301\3f\17gH\0"
	.data
	.align 32
_instrux_PACKUSWB:
	.long	343
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC839
	.long	83902465
	.long	343
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC840
	.long	83902464
	.long	343
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC841
	.long	134348800
	.long	343
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC842
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC843:
	.ascii "\301\2\17\374H\0"
LC844:
	.ascii "\2\17\374H\0"
LC845:
	.ascii "\3f\17\374H\0"
LC846:
	.ascii "\301\3f\17\374H\0"
	.data
	.align 32
_instrux_PADDB:
	.long	344
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC843
	.long	83902465
	.long	344
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC844
	.long	83902464
	.long	344
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC845
	.long	134348800
	.long	344
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC846
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC847:
	.ascii "\301\2\17\376H\0"
LC848:
	.ascii "\2\17\376H\0"
LC849:
	.ascii "\3f\17\376H\0"
LC850:
	.ascii "\301\3f\17\376H\0"
	.data
	.align 32
_instrux_PADDD:
	.long	345
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC847
	.long	83902465
	.long	345
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC848
	.long	83902464
	.long	345
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC849
	.long	134348800
	.long	345
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC850
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC851:
	.ascii "\2\17\324H\0"
LC852:
	.ascii "\301\2\17\324H\0"
LC853:
	.ascii "\3f\17\324H\0"
LC854:
	.ascii "\301\3f\17\324H\0"
	.data
	.align 32
_instrux_PADDQ:
	.long	346
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC851
	.long	134348800
	.long	346
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC852
	.long	134348801
	.long	346
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC853
	.long	134348800
	.long	346
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC854
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC855:
	.ascii "\301\2\17\354H\0"
LC856:
	.ascii "\2\17\354H\0"
LC857:
	.ascii "\301\3f\17\354H\0"
LC858:
	.ascii "\3f\17\354H\0"
	.data
	.align 32
_instrux_PADDSB:
	.long	347
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC855
	.long	83902465
	.long	347
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC856
	.long	83902464
	.long	347
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC857
	.long	134348801
	.long	347
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC858
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC859:
	.ascii "\301\2\17QH\0"
LC860:
	.ascii "\2\17QH\0"
	.data
	.align 32
_instrux_PADDSIW:
	.long	348
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC859
	.long	352337921
	.long	348
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC860
	.long	352337920
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC861:
	.ascii "\301\2\17\355H\0"
LC862:
	.ascii "\2\17\355H\0"
LC863:
	.ascii "\301\3f\17\355H\0"
LC864:
	.ascii "\3f\17\355H\0"
	.data
	.align 32
_instrux_PADDSW:
	.long	349
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC861
	.long	83902465
	.long	349
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC862
	.long	83902464
	.long	349
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC863
	.long	134348801
	.long	349
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC864
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC865:
	.ascii "\301\2\17\334H\0"
LC866:
	.ascii "\2\17\334H\0"
LC867:
	.ascii "\301\3f\17\334H\0"
LC868:
	.ascii "\3f\17\334H\0"
	.data
	.align 32
_instrux_PADDUSB:
	.long	350
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC865
	.long	83902465
	.long	350
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC866
	.long	83902464
	.long	350
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC867
	.long	134348801
	.long	350
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC868
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC869:
	.ascii "\301\2\17\335H\0"
LC870:
	.ascii "\2\17\335H\0"
LC871:
	.ascii "\301\3f\17\335H\0"
LC872:
	.ascii "\3f\17\335H\0"
	.data
	.align 32
_instrux_PADDUSW:
	.long	351
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC869
	.long	83902465
	.long	351
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC870
	.long	83902464
	.long	351
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC871
	.long	134348801
	.long	351
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC872
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC873:
	.ascii "\301\2\17\375H\0"
LC874:
	.ascii "\2\17\375H\0"
LC875:
	.ascii "\3f\17\375H\0"
LC876:
	.ascii "\301\3f\17\375H\0"
	.data
	.align 32
_instrux_PADDW:
	.long	352
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC873
	.long	83902465
	.long	352
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC874
	.long	83902464
	.long	352
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC875
	.long	134348800
	.long	352
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC876
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC877:
	.ascii "\301\2\17\333H\0"
LC878:
	.ascii "\2\17\333H\0"
LC879:
	.ascii "\3f\17\333H\0"
LC880:
	.ascii "\301\3f\17\333H\0"
	.data
	.align 32
_instrux_PAND:
	.long	353
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC877
	.long	83902465
	.long	353
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC878
	.long	83902464
	.long	353
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC879
	.long	134348800
	.long	353
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC880
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC881:
	.ascii "\301\2\17\337H\0"
LC882:
	.ascii "\2\17\337H\0"
LC883:
	.ascii "\3f\17\337H\0"
LC884:
	.ascii "\301\3f\17\337H\0"
	.data
	.align 32
_instrux_PANDN:
	.long	354
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC881
	.long	83902465
	.long	354
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC882
	.long	83902464
	.long	354
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC883
	.long	134348800
	.long	354
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC884
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC885:
	.ascii "\333\1\220\0"
	.data
	.align 32
_instrux_PAUSE:
	.long	355
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC885
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC886:
	.ascii "\301\2\17PH\0"
	.data
	.align 32
_instrux_PAVEB:
	.long	356
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC886
	.long	352337921
	.long	356
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC731
	.long	352337920
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC887:
	.ascii "\2\17\340H\0"
LC888:
	.ascii "\301\2\17\340H\0"
LC889:
	.ascii "\3f\17\340H\0"
LC890:
	.ascii "\301\3f\17\340H\0"
	.data
	.align 32
_instrux_PAVGB:
	.long	357
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC887
	.long	117456896
	.long	357
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC888
	.long	117456897
	.long	357
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC889
	.long	134348800
	.long	357
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC890
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC891:
	.ascii "\301\2\17\17H\1\277\0"
LC892:
	.ascii "\2\17\17H\1\277\0"
	.data
	.align 32
_instrux_PAVGUSB:
	.long	358
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC891
	.long	83918849
	.long	358
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC892
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC893:
	.ascii "\2\17\343H\0"
LC894:
	.ascii "\301\2\17\343H\0"
LC895:
	.ascii "\3f\17\343H\0"
LC896:
	.ascii "\301\3f\17\343H\0"
	.data
	.align 32
_instrux_PAVGW:
	.long	359
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC893
	.long	117456896
	.long	359
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC894
	.long	117456897
	.long	359
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC895
	.long	134348800
	.long	359
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC896
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC897:
	.ascii "\301\2\17tH\0"
LC898:
	.ascii "\2\17tH\0"
LC899:
	.ascii "\3f\17tH\0"
LC900:
	.ascii "\301\3f\17tH\0"
	.data
	.align 32
_instrux_PCMPEQB:
	.long	360
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC897
	.long	83902465
	.long	360
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC898
	.long	83902464
	.long	360
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC899
	.long	134348800
	.long	360
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC900
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC901:
	.ascii "\301\2\17vH\0"
LC902:
	.ascii "\2\17vH\0"
LC903:
	.ascii "\3f\17vH\0"
LC904:
	.ascii "\301\3f\17vH\0"
	.data
	.align 32
_instrux_PCMPEQD:
	.long	361
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC901
	.long	83902465
	.long	361
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC902
	.long	83902464
	.long	361
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC903
	.long	134348800
	.long	361
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC904
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC905:
	.ascii "\301\2\17uH\0"
LC906:
	.ascii "\2\17uH\0"
LC907:
	.ascii "\3f\17uH\0"
LC908:
	.ascii "\301\3f\17uH\0"
	.data
	.align 32
_instrux_PCMPEQW:
	.long	362
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC905
	.long	83902465
	.long	362
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC906
	.long	83902464
	.long	362
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC907
	.long	134348800
	.long	362
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC908
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC909:
	.ascii "\301\2\17dH\0"
LC910:
	.ascii "\2\17dH\0"
LC911:
	.ascii "\3f\17dH\0"
LC912:
	.ascii "\301\3f\17dH\0"
	.data
	.align 32
_instrux_PCMPGTB:
	.long	363
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC909
	.long	83902465
	.long	363
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC910
	.long	83902464
	.long	363
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC911
	.long	134348800
	.long	363
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC912
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC913:
	.ascii "\301\2\17fH\0"
LC914:
	.ascii "\2\17fH\0"
LC915:
	.ascii "\3f\17fH\0"
LC916:
	.ascii "\301\3f\17fH\0"
	.data
	.align 32
_instrux_PCMPGTD:
	.long	364
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC913
	.long	83902465
	.long	364
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC914
	.long	83902464
	.long	364
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC915
	.long	134348800
	.long	364
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC916
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC917:
	.ascii "\301\2\17eH\0"
LC918:
	.ascii "\2\17eH\0"
LC919:
	.ascii "\3f\17eH\0"
LC920:
	.ascii "\301\3f\17eH\0"
	.data
	.align 32
_instrux_PCMPGTW:
	.long	365
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC917
	.long	83902465
	.long	365
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC918
	.long	83902464
	.long	365
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC919
	.long	134348800
	.long	365
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC920
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_PDISTIB:
	.long	366
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC90
	.long	352337921
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC921:
	.ascii "\2\17\305H\26\0"
LC922:
	.ascii "\3f\17\305H\26\0"
	.data
	.align 32
_instrux_PEXTRW:
	.long	367
	.long	3
	.long	2101252
	.long	2101256
	.long	8192
	.long	LC921
	.long	117456996
	.long	367
	.long	3
	.long	2101252
	.long	2101264
	.long	8192
	.long	LC922
	.long	134348900
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC923:
	.ascii "\301\2\17\17H\1\35\0"
LC924:
	.ascii "\2\17\17H\1\35\0"
	.data
	.align 32
_instrux_PF2ID:
	.long	368
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC923
	.long	83918849
	.long	368
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC924
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC925:
	.ascii "\301\2\17\17H\1\34\0"
LC926:
	.ascii "\2\17\17H\1\34\0"
	.data
	.align 32
_instrux_PF2IW:
	.long	369
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC925
	.long	83918849
	.long	369
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC926
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC927:
	.ascii "\301\2\17\17H\1\256\0"
LC928:
	.ascii "\2\17\17H\1\256\0"
	.data
	.align 32
_instrux_PFACC:
	.long	370
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC927
	.long	83918849
	.long	370
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC928
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC929:
	.ascii "\301\2\17\17H\1\236\0"
LC930:
	.ascii "\2\17\17H\1\236\0"
	.data
	.align 32
_instrux_PFADD:
	.long	371
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC929
	.long	83918849
	.long	371
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC930
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC931:
	.ascii "\301\2\17\17H\1\260\0"
LC932:
	.ascii "\2\17\17H\1\260\0"
	.data
	.align 32
_instrux_PFCMPEQ:
	.long	372
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC931
	.long	83918849
	.long	372
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC932
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC933:
	.ascii "\301\2\17\17H\1\220\0"
LC934:
	.ascii "\2\17\17H\1\220\0"
	.data
	.align 32
_instrux_PFCMPGE:
	.long	373
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC933
	.long	83918849
	.long	373
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC934
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC935:
	.ascii "\301\2\17\17H\1\240\0"
LC936:
	.ascii "\2\17\17H\1\240\0"
	.data
	.align 32
_instrux_PFCMPGT:
	.long	374
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC935
	.long	83918849
	.long	374
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC936
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC937:
	.ascii "\301\2\17\17H\1\244\0"
LC938:
	.ascii "\2\17\17H\1\244\0"
	.data
	.align 32
_instrux_PFMAX:
	.long	375
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC937
	.long	83918849
	.long	375
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC938
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC939:
	.ascii "\301\2\17\17H\1\224\0"
LC940:
	.ascii "\2\17\17H\1\224\0"
	.data
	.align 32
_instrux_PFMIN:
	.long	376
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC939
	.long	83918849
	.long	376
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC940
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC941:
	.ascii "\301\2\17\17H\1\264\0"
LC942:
	.ascii "\2\17\17H\1\264\0"
	.data
	.align 32
_instrux_PFMUL:
	.long	377
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC941
	.long	83918849
	.long	377
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC942
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC943:
	.ascii "\301\2\17\17H\1\212\0"
LC944:
	.ascii "\2\17\17H\1\212\0"
	.data
	.align 32
_instrux_PFNACC:
	.long	378
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC943
	.long	83918849
	.long	378
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC944
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC945:
	.ascii "\301\2\17\17H\1\216\0"
LC946:
	.ascii "\2\17\17H\1\216\0"
	.data
	.align 32
_instrux_PFPNACC:
	.long	379
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC945
	.long	83918849
	.long	379
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC946
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC947:
	.ascii "\301\2\17\17H\1\226\0"
LC948:
	.ascii "\2\17\17H\1\226\0"
	.data
	.align 32
_instrux_PFRCP:
	.long	380
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC947
	.long	83918849
	.long	380
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC948
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC949:
	.ascii "\301\2\17\17H\1\246\0"
LC950:
	.ascii "\2\17\17H\1\246\0"
	.data
	.align 32
_instrux_PFRCPIT1:
	.long	381
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC949
	.long	83918849
	.long	381
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC950
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC951:
	.ascii "\301\2\17\17H\1\266\0"
LC952:
	.ascii "\2\17\17H\1\266\0"
	.data
	.align 32
_instrux_PFRCPIT2:
	.long	382
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC951
	.long	83918849
	.long	382
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC952
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC953:
	.ascii "\301\2\17\17H\1\247\0"
LC954:
	.ascii "\2\17\17H\1\247\0"
	.data
	.align 32
_instrux_PFRSQIT1:
	.long	383
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC953
	.long	83918849
	.long	383
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC954
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC955:
	.ascii "\301\2\17\17H\1\227\0"
LC956:
	.ascii "\2\17\17H\1\227\0"
	.data
	.align 32
_instrux_PFRSQRT:
	.long	384
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC955
	.long	83918849
	.long	384
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC956
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC957:
	.ascii "\301\2\17\17H\1\232\0"
LC958:
	.ascii "\2\17\17H\1\232\0"
	.data
	.align 32
_instrux_PFSUB:
	.long	385
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC957
	.long	83918849
	.long	385
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC958
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC959:
	.ascii "\301\2\17\17H\1\252\0"
LC960:
	.ascii "\2\17\17H\1\252\0"
	.data
	.align 32
_instrux_PFSUBR:
	.long	386
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC959
	.long	83918849
	.long	386
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC960
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC961:
	.ascii "\301\2\17\17H\1\15\0"
LC962:
	.ascii "\2\17\17H\1\15\0"
	.data
	.align 32
_instrux_PI2FD:
	.long	387
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC961
	.long	83918849
	.long	387
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC962
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC963:
	.ascii "\301\2\17\17H\1\14\0"
LC964:
	.ascii "\2\17\17H\1\14\0"
	.data
	.align 32
_instrux_PI2FW:
	.long	388
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC963
	.long	83918849
	.long	388
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC964
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC965:
	.ascii "\2\17\304H\26\0"
LC966:
	.ascii "\301\2\17\304H\26\0"
LC967:
	.ascii "\3f\17\304H\26\0"
LC968:
	.ascii "\301\3f\17\304H\26\0"
	.data
	.align 32
_instrux_PINSRW:
	.long	389
	.long	3
	.long	2101256
	.long	2101250
	.long	8192
	.long	LC965
	.long	117456996
	.long	389
	.long	3
	.long	2101256
	.long	2101252
	.long	8192
	.long	LC965
	.long	117456996
	.long	389
	.long	3
	.long	2101256
	.long	2113536
	.long	8192
	.long	LC966
	.long	117456996
	.long	389
	.long	3
	.long	2101256
	.long	2113538
	.long	8192
	.long	LC966
	.long	117456996
	.long	389
	.long	3
	.long	2101264
	.long	2101250
	.long	8192
	.long	LC967
	.long	134348900
	.long	389
	.long	3
	.long	2101264
	.long	2101252
	.long	8192
	.long	LC967
	.long	134348900
	.long	389
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC968
	.long	134348900
	.long	389
	.long	3
	.long	2101264
	.long	2113538
	.long	8192
	.long	LC968
	.long	134348900
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC969:
	.ascii "\301\2\17^H\0"
	.data
	.align 32
_instrux_PMACHRIW:
	.long	390
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC969
	.long	352337921
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC970:
	.ascii "\301\2\17\365H\0"
LC971:
	.ascii "\2\17\365H\0"
LC972:
	.ascii "\301\3f\17\365H\0"
LC973:
	.ascii "\3f\17\365H\0"
	.data
	.align 32
_instrux_PMADDWD:
	.long	391
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC970
	.long	83902465
	.long	391
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC971
	.long	83902464
	.long	391
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC972
	.long	134348801
	.long	391
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC973
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC974:
	.ascii "\301\2\17RH\0"
LC975:
	.ascii "\2\17RH\0"
	.data
	.align 32
_instrux_PMAGW:
	.long	392
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC974
	.long	352337921
	.long	392
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC975
	.long	352337920
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC976:
	.ascii "\2\17\356H\0"
LC977:
	.ascii "\301\2\17\356H\0"
LC978:
	.ascii "\3f\17\356H\0"
LC979:
	.ascii "\301\3f\17\356H\0"
	.data
	.align 32
_instrux_PMAXSW:
	.long	393
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC976
	.long	117456896
	.long	393
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC977
	.long	117456897
	.long	393
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC978
	.long	134348800
	.long	393
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC979
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC980:
	.ascii "\2\17\336H\0"
LC981:
	.ascii "\301\2\17\336H\0"
LC982:
	.ascii "\3f\17\336H\0"
LC983:
	.ascii "\301\3f\17\336H\0"
	.data
	.align 32
_instrux_PMAXUB:
	.long	394
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC980
	.long	117456896
	.long	394
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC981
	.long	117456897
	.long	394
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC982
	.long	134348800
	.long	394
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC983
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC984:
	.ascii "\2\17\352H\0"
LC985:
	.ascii "\301\2\17\352H\0"
LC986:
	.ascii "\3f\17\352H\0"
LC987:
	.ascii "\301\3f\17\352H\0"
	.data
	.align 32
_instrux_PMINSW:
	.long	395
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC984
	.long	117456896
	.long	395
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC985
	.long	117456897
	.long	395
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC986
	.long	134348800
	.long	395
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC987
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC988:
	.ascii "\2\17\332H\0"
LC989:
	.ascii "\301\2\17\332H\0"
LC990:
	.ascii "\3f\17\332H\0"
LC991:
	.ascii "\301\3f\17\332H\0"
	.data
	.align 32
_instrux_PMINUB:
	.long	396
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC988
	.long	117456896
	.long	396
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC989
	.long	117456897
	.long	396
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC990
	.long	134348800
	.long	396
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC991
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC992:
	.ascii "\2\17\327H\0"
LC993:
	.ascii "\3f\17\327H\0"
	.data
	.align 32
_instrux_PMOVMSKB:
	.long	397
	.long	2
	.long	2101252
	.long	2101256
	.long	0
	.long	LC992
	.long	117456896
	.long	397
	.long	2
	.long	2101252
	.long	2101264
	.long	0
	.long	LC993
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC994:
	.ascii "\301\2\17]H\0"
LC995:
	.ascii "\2\17]H\0"
	.data
	.align 32
_instrux_PMULHRIW:
	.long	398
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC994
	.long	352337921
	.long	398
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC995
	.long	352337920
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC996:
	.ascii "\301\2\17\17H\1\267\0"
LC997:
	.ascii "\2\17\17H\1\267\0"
	.data
	.align 32
_instrux_PMULHRWA:
	.long	399
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC996
	.long	83918849
	.long	399
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC997
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_PMULHRWC:
	.long	400
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC782
	.long	352337921
	.long	400
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC783
	.long	352337920
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC998:
	.ascii "\2\17\344H\0"
LC999:
	.ascii "\301\2\17\344H\0"
LC1000:
	.ascii "\3f\17\344H\0"
LC1001:
	.ascii "\301\3f\17\344H\0"
	.data
	.align 32
_instrux_PMULHUW:
	.long	401
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC998
	.long	117456896
	.long	401
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC999
	.long	117456897
	.long	401
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1000
	.long	134348800
	.long	401
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1001
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1002:
	.ascii "\301\2\17\345H\0"
LC1003:
	.ascii "\2\17\345H\0"
LC1004:
	.ascii "\301\3f\17\345H\0"
LC1005:
	.ascii "\3f\17\345H\0"
	.data
	.align 32
_instrux_PMULHW:
	.long	402
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1002
	.long	83902465
	.long	402
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1003
	.long	83902464
	.long	402
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1004
	.long	134348801
	.long	402
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1005
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1006:
	.ascii "\301\2\17\325H\0"
LC1007:
	.ascii "\2\17\325H\0"
LC1008:
	.ascii "\301\3f\17\325H\0"
LC1009:
	.ascii "\3f\17\325H\0"
	.data
	.align 32
_instrux_PMULLW:
	.long	403
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1006
	.long	83902465
	.long	403
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1007
	.long	83902464
	.long	403
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1008
	.long	134348801
	.long	403
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1009
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1010:
	.ascii "\2\17\364H\0"
LC1011:
	.ascii "\301\2\17\364H\0"
LC1012:
	.ascii "\3f\17\364H\0"
LC1013:
	.ascii "\301\3f\17\364H\0"
	.data
	.align 32
_instrux_PMULUDQ:
	.long	404
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1010
	.long	134348800
	.long	404
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1011
	.long	134348801
	.long	404
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1012
	.long	134348800
	.long	404
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1013
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1014:
	.ascii "\301\2\17\\H\0"
	.data
	.align 32
_instrux_PMVGEZB:
	.long	405
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1014
	.long	352337921
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_PMVLZB:
	.long	406
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC270
	.long	352337921
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_PMVNZB:
	.long	407
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC284
	.long	352337921
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1015:
	.ascii "\301\2\17XH\0"
	.data
	.align 32
_instrux_PMVZB:
	.long	408
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1015
	.long	352337921
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1016:
	.ascii "\320\10X\0"
LC1017:
	.ascii "\321\10X\0"
LC1018:
	.ascii "\320\300\1\217\200\0"
LC1019:
	.ascii "\321\300\1\217\200\0"
LC1020:
	.ascii "\1\17\0"
LC1021:
	.ascii "\4\0"
LC1022:
	.ascii "\1\17\5\0"
	.data
	.align 32
_instrux_POP:
	.long	409
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1016
	.long	0
	.long	409
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC1017
	.long	50331648
	.long	409
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC1018
	.long	0
	.long	409
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC1019
	.long	50331648
	.long	409
	.long	1
	.long	17305602
	.long	0
	.long	0
	.long	LC1020
	.long	4096
	.long	409
	.long	1
	.long	34082818
	.long	0
	.long	0
	.long	LC1021
	.long	0
	.long	409
	.long	1
	.long	67637250
	.long	0
	.long	0
	.long	LC1022
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1023:
	.ascii "\322\1a\0"
	.data
	.align 32
_instrux_POPA:
	.long	410
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1023
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1024:
	.ascii "\321\1a\0"
	.data
	.align 32
_instrux_POPAD:
	.long	411
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1024
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1025:
	.ascii "\320\1a\0"
	.data
	.align 32
_instrux_POPAW:
	.long	412
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1025
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1026:
	.ascii "\322\1\235\0"
	.data
	.align 32
_instrux_POPF:
	.long	413
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1026
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1027:
	.ascii "\321\1\235\0"
	.data
	.align 32
_instrux_POPFD:
	.long	414
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1027
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1028:
	.ascii "\320\1\235\0"
	.data
	.align 32
_instrux_POPFW:
	.long	415
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1028
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1029:
	.ascii "\301\2\17\353H\0"
LC1030:
	.ascii "\2\17\353H\0"
LC1031:
	.ascii "\301\3f\17\353H\0"
LC1032:
	.ascii "\3f\17\353H\0"
	.data
	.align 32
_instrux_POR:
	.long	416
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1029
	.long	83902465
	.long	416
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1030
	.long	83902464
	.long	416
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1031
	.long	134348801
	.long	416
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1032
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1033:
	.ascii "\2\17\15\200\0"
	.data
	.align 32
_instrux_PREFETCH:
	.long	417
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1033
	.long	83918849
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1034:
	.ascii "\300\2\17\30\200\0"
	.data
	.align 32
_instrux_PREFETCHNTA:
	.long	418
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1034
	.long	117440512
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1035:
	.ascii "\300\2\17\30\201\0"
	.data
	.align 32
_instrux_PREFETCHT0:
	.long	419
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1035
	.long	117440512
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1036:
	.ascii "\300\2\17\30\202\0"
	.data
	.align 32
_instrux_PREFETCHT1:
	.long	420
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1036
	.long	117440512
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1037:
	.ascii "\300\2\17\30\203\0"
	.data
	.align 32
_instrux_PREFETCHT2:
	.long	421
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1037
	.long	117440512
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1038:
	.ascii "\2\17\15\201\0"
	.data
	.align 32
_instrux_PREFETCHW:
	.long	422
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1038
	.long	83918849
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1039:
	.ascii "\2\17\366H\0"
LC1040:
	.ascii "\301\2\17\366H\0"
LC1041:
	.ascii "\3f\17\366H\0"
LC1042:
	.ascii "\301\3f\17\366H\0"
	.data
	.align 32
_instrux_PSADBW:
	.long	423
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1039
	.long	117456896
	.long	423
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1040
	.long	117456897
	.long	423
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1041
	.long	134348800
	.long	423
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1042
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1043:
	.ascii "\3f\17pH\22\0"
LC1044:
	.ascii "\301\3f\17pH\22\0"
	.data
	.align 32
_instrux_PSHUFD:
	.long	424
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC1043
	.long	134348900
	.long	424
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC1044
	.long	134348902
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1045:
	.ascii "\333\2\17pH\22\0"
LC1046:
	.ascii "\301\333\2\17pH\22\0"
	.data
	.align 32
_instrux_PSHUFHW:
	.long	425
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC1045
	.long	134348900
	.long	425
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC1046
	.long	134348902
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1047:
	.ascii "\3\362\17pH\22\0"
LC1048:
	.ascii "\301\3\362\17pH\22\0"
	.data
	.align 32
_instrux_PSHUFLW:
	.long	426
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC1047
	.long	134348900
	.long	426
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC1048
	.long	134348902
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1049:
	.ascii "\2\17pH\22\0"
LC1050:
	.ascii "\301\2\17pH\22\0"
	.data
	.align 32
_instrux_PSHUFW:
	.long	427
	.long	3
	.long	2101256
	.long	2101256
	.long	8192
	.long	LC1049
	.long	117456996
	.long	427
	.long	3
	.long	2101256
	.long	2113536
	.long	8192
	.long	LC1050
	.long	117456998
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1051:
	.ascii "\301\2\17\362H\0"
LC1052:
	.ascii "\2\17\362H\0"
LC1053:
	.ascii "\2\17r\206\25\0"
LC1054:
	.ascii "\301\3f\17\362H\0"
LC1055:
	.ascii "\3f\17\362H\0"
LC1056:
	.ascii "\3f\17r\206\25\0"
	.data
	.align 32
_instrux_PSLLD:
	.long	428
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1051
	.long	83902465
	.long	428
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1052
	.long	83902464
	.long	428
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1053
	.long	83902464
	.long	428
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1054
	.long	134348801
	.long	428
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1055
	.long	134348800
	.long	428
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1056
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1057:
	.ascii "\3f\17s\207\25\0"
	.data
	.align 32
_instrux_PSLLDQ:
	.long	429
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1057
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1058:
	.ascii "\301\2\17\363H\0"
LC1059:
	.ascii "\2\17\363H\0"
LC1060:
	.ascii "\2\17s\206\25\0"
LC1061:
	.ascii "\301\3f\17\363H\0"
LC1062:
	.ascii "\3f\17\363H\0"
LC1063:
	.ascii "\3f\17s\206\25\0"
	.data
	.align 32
_instrux_PSLLQ:
	.long	430
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1058
	.long	83902465
	.long	430
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1059
	.long	83902464
	.long	430
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1060
	.long	83902464
	.long	430
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1061
	.long	134348801
	.long	430
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1062
	.long	134348800
	.long	430
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1063
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1064:
	.ascii "\301\2\17\361H\0"
LC1065:
	.ascii "\2\17\361H\0"
LC1066:
	.ascii "\2\17q\206\25\0"
LC1067:
	.ascii "\301\3f\17\361H\0"
LC1068:
	.ascii "\3f\17\361H\0"
LC1069:
	.ascii "\3f\17q\206\25\0"
	.data
	.align 32
_instrux_PSLLW:
	.long	431
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1064
	.long	83902465
	.long	431
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1065
	.long	83902464
	.long	431
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1066
	.long	83902464
	.long	431
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1067
	.long	134348801
	.long	431
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1068
	.long	134348800
	.long	431
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1069
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1070:
	.ascii "\301\2\17\342H\0"
LC1071:
	.ascii "\2\17\342H\0"
LC1072:
	.ascii "\2\17r\204\25\0"
LC1073:
	.ascii "\301\3f\17\342H\0"
LC1074:
	.ascii "\3f\17\342H\0"
LC1075:
	.ascii "\3f\17r\204\25\0"
	.data
	.align 32
_instrux_PSRAD:
	.long	432
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1070
	.long	83902465
	.long	432
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1071
	.long	83902464
	.long	432
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1072
	.long	83902464
	.long	432
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1073
	.long	134348801
	.long	432
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1074
	.long	134348800
	.long	432
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1075
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1076:
	.ascii "\301\2\17\341H\0"
LC1077:
	.ascii "\2\17\341H\0"
LC1078:
	.ascii "\2\17q\204\25\0"
LC1079:
	.ascii "\301\3f\17\341H\0"
LC1080:
	.ascii "\3f\17\341H\0"
LC1081:
	.ascii "\3f\17q\204\25\0"
	.data
	.align 32
_instrux_PSRAW:
	.long	433
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1076
	.long	83902465
	.long	433
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1077
	.long	83902464
	.long	433
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1078
	.long	83902464
	.long	433
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1079
	.long	134348801
	.long	433
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1080
	.long	134348800
	.long	433
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1081
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1082:
	.ascii "\301\2\17\322H\0"
LC1083:
	.ascii "\2\17\322H\0"
LC1084:
	.ascii "\2\17r\202\25\0"
LC1085:
	.ascii "\301\3f\17\322H\0"
LC1086:
	.ascii "\3f\17\322H\0"
LC1087:
	.ascii "\3f\17r\202\25\0"
	.data
	.align 32
_instrux_PSRLD:
	.long	434
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1082
	.long	83902465
	.long	434
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1083
	.long	83902464
	.long	434
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1084
	.long	83902464
	.long	434
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1085
	.long	134348801
	.long	434
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1086
	.long	134348800
	.long	434
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1087
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1088:
	.ascii "\3f\17s\203\25\0"
	.data
	.align 32
_instrux_PSRLDQ:
	.long	435
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1088
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1089:
	.ascii "\301\2\17\323H\0"
LC1090:
	.ascii "\2\17\323H\0"
LC1091:
	.ascii "\2\17s\202\25\0"
LC1092:
	.ascii "\301\3f\17\323H\0"
LC1093:
	.ascii "\3f\17\323H\0"
LC1094:
	.ascii "\3f\17s\202\25\0"
	.data
	.align 32
_instrux_PSRLQ:
	.long	436
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1089
	.long	83902465
	.long	436
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1090
	.long	83902464
	.long	436
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1091
	.long	83902464
	.long	436
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1092
	.long	134348801
	.long	436
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1093
	.long	134348800
	.long	436
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1094
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1095:
	.ascii "\301\2\17\321H\0"
LC1096:
	.ascii "\2\17\321H\0"
LC1097:
	.ascii "\2\17q\202\25\0"
LC1098:
	.ascii "\301\3f\17\321H\0"
LC1099:
	.ascii "\3f\17\321H\0"
LC1100:
	.ascii "\3f\17q\202\25\0"
	.data
	.align 32
_instrux_PSRLW:
	.long	437
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1095
	.long	83902465
	.long	437
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1096
	.long	83902464
	.long	437
	.long	2
	.long	2101256
	.long	8192
	.long	0
	.long	LC1097
	.long	83902464
	.long	437
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1098
	.long	134348801
	.long	437
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1099
	.long	134348800
	.long	437
	.long	2
	.long	2101264
	.long	8192
	.long	0
	.long	LC1100
	.long	134348868
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1101:
	.ascii "\301\2\17\370H\0"
LC1102:
	.ascii "\2\17\370H\0"
LC1103:
	.ascii "\301\3f\17\370H\0"
LC1104:
	.ascii "\3f\17\370H\0"
	.data
	.align 32
_instrux_PSUBB:
	.long	438
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1101
	.long	83902465
	.long	438
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1102
	.long	83902464
	.long	438
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1103
	.long	134348801
	.long	438
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1104
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1105:
	.ascii "\301\2\17\372H\0"
LC1106:
	.ascii "\2\17\372H\0"
LC1107:
	.ascii "\301\3f\17\372H\0"
LC1108:
	.ascii "\3f\17\372H\0"
	.data
	.align 32
_instrux_PSUBD:
	.long	439
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1105
	.long	83902465
	.long	439
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1106
	.long	83902464
	.long	439
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1107
	.long	134348801
	.long	439
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1108
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1109:
	.ascii "\2\17\373H\0"
LC1110:
	.ascii "\301\2\17\373H\0"
LC1111:
	.ascii "\3f\17\373H\0"
LC1112:
	.ascii "\301\3f\17\373H\0"
	.data
	.align 32
_instrux_PSUBQ:
	.long	440
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1109
	.long	134348800
	.long	440
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1110
	.long	134348801
	.long	440
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1111
	.long	134348800
	.long	440
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1112
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1113:
	.ascii "\301\2\17\350H\0"
LC1114:
	.ascii "\2\17\350H\0"
LC1115:
	.ascii "\301\3f\17\350H\0"
LC1116:
	.ascii "\3f\17\350H\0"
	.data
	.align 32
_instrux_PSUBSB:
	.long	441
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1113
	.long	83902465
	.long	441
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1114
	.long	83902464
	.long	441
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1115
	.long	134348801
	.long	441
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1116
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_PSUBSIW:
	.long	442
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC86
	.long	352337921
	.long	442
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC87
	.long	352337920
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1117:
	.ascii "\301\2\17\351H\0"
LC1118:
	.ascii "\2\17\351H\0"
LC1119:
	.ascii "\301\3f\17\351H\0"
LC1120:
	.ascii "\3f\17\351H\0"
	.data
	.align 32
_instrux_PSUBSW:
	.long	443
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1117
	.long	83902465
	.long	443
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1118
	.long	83902464
	.long	443
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1119
	.long	134348801
	.long	443
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1120
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1121:
	.ascii "\301\2\17\330H\0"
LC1122:
	.ascii "\2\17\330H\0"
LC1123:
	.ascii "\301\3f\17\330H\0"
LC1124:
	.ascii "\3f\17\330H\0"
	.data
	.align 32
_instrux_PSUBUSB:
	.long	444
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1121
	.long	83902465
	.long	444
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1122
	.long	83902464
	.long	444
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1123
	.long	134348801
	.long	444
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1124
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1125:
	.ascii "\301\2\17\331H\0"
LC1126:
	.ascii "\2\17\331H\0"
LC1127:
	.ascii "\301\3f\17\331H\0"
LC1128:
	.ascii "\3f\17\331H\0"
	.data
	.align 32
_instrux_PSUBUSW:
	.long	445
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1125
	.long	83902465
	.long	445
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1126
	.long	83902464
	.long	445
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1127
	.long	134348801
	.long	445
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1128
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1129:
	.ascii "\301\2\17\371H\0"
LC1130:
	.ascii "\2\17\371H\0"
LC1131:
	.ascii "\301\3f\17\371H\0"
LC1132:
	.ascii "\3f\17\371H\0"
	.data
	.align 32
_instrux_PSUBW:
	.long	446
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1129
	.long	83902465
	.long	446
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1130
	.long	83902464
	.long	446
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1131
	.long	134348801
	.long	446
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1132
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1133:
	.ascii "\301\2\17\17H\1\273\0"
LC1134:
	.ascii "\2\17\17H\1\273\0"
	.data
	.align 32
_instrux_PSWAPD:
	.long	447
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1133
	.long	83918849
	.long	447
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1134
	.long	83918848
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1135:
	.ascii "\301\2\17hH\0"
LC1136:
	.ascii "\2\17hH\0"
LC1137:
	.ascii "\301\3f\17hH\0"
LC1138:
	.ascii "\3f\17hH\0"
	.data
	.align 32
_instrux_PUNPCKHBW:
	.long	448
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1135
	.long	83902465
	.long	448
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1136
	.long	83902464
	.long	448
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1137
	.long	134348801
	.long	448
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1138
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1139:
	.ascii "\301\2\17jH\0"
LC1140:
	.ascii "\2\17jH\0"
LC1141:
	.ascii "\301\3f\17jH\0"
LC1142:
	.ascii "\3f\17jH\0"
	.data
	.align 32
_instrux_PUNPCKHDQ:
	.long	449
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1139
	.long	83902465
	.long	449
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1140
	.long	83902464
	.long	449
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1141
	.long	134348801
	.long	449
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1142
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1143:
	.ascii "\3f\17mH\0"
LC1144:
	.ascii "\301\3f\17mH\0"
	.data
	.align 32
_instrux_PUNPCKHQDQ:
	.long	450
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1143
	.long	134348800
	.long	450
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1144
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1145:
	.ascii "\301\2\17iH\0"
LC1146:
	.ascii "\2\17iH\0"
LC1147:
	.ascii "\301\3f\17iH\0"
LC1148:
	.ascii "\3f\17iH\0"
	.data
	.align 32
_instrux_PUNPCKHWD:
	.long	451
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1145
	.long	83902465
	.long	451
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1146
	.long	83902464
	.long	451
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1147
	.long	134348801
	.long	451
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1148
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1149:
	.ascii "\301\2\17`H\0"
LC1150:
	.ascii "\2\17`H\0"
LC1151:
	.ascii "\301\3f\17`H\0"
LC1152:
	.ascii "\3f\17`H\0"
	.data
	.align 32
_instrux_PUNPCKLBW:
	.long	452
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1149
	.long	83902465
	.long	452
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1150
	.long	83902464
	.long	452
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1151
	.long	134348801
	.long	452
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1152
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1153:
	.ascii "\301\2\17bH\0"
LC1154:
	.ascii "\2\17bH\0"
LC1155:
	.ascii "\301\3f\17bH\0"
LC1156:
	.ascii "\3f\17bH\0"
	.data
	.align 32
_instrux_PUNPCKLDQ:
	.long	453
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1153
	.long	83902465
	.long	453
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1154
	.long	83902464
	.long	453
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1155
	.long	134348801
	.long	453
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1156
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1157:
	.ascii "\3f\17lH\0"
LC1158:
	.ascii "\301\3f\17lH\0"
	.data
	.align 32
_instrux_PUNPCKLQDQ:
	.long	454
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1157
	.long	134348800
	.long	454
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1158
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1159:
	.ascii "\301\2\17aH\0"
LC1160:
	.ascii "\2\17aH\0"
LC1161:
	.ascii "\301\3f\17aH\0"
LC1162:
	.ascii "\3f\17aH\0"
	.data
	.align 32
_instrux_PUNPCKLWD:
	.long	455
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1159
	.long	83902465
	.long	455
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1160
	.long	83902464
	.long	455
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1161
	.long	134348801
	.long	455
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1162
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1163:
	.ascii "\320\10P\0"
LC1164:
	.ascii "\321\10P\0"
LC1165:
	.ascii "\320\300\1\377\206\0"
LC1166:
	.ascii "\321\300\1\377\206\0"
LC1167:
	.ascii "\6\0"
LC1168:
	.ascii "\1\17\7\0"
LC1169:
	.ascii "\1j\14\0"
LC1170:
	.ascii "\320[\1hX\0"
LC1171:
	.ascii "\321c\1h`\0"
LC1172:
	.ascii "\1h\34\0"
	.data
	.align 32
_instrux_PUSH:
	.long	456
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1163
	.long	0
	.long	456
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC1164
	.long	50331648
	.long	456
	.long	1
	.long	2097154
	.long	0
	.long	0
	.long	LC1165
	.long	0
	.long	456
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC1166
	.long	50331648
	.long	456
	.long	1
	.long	17305602
	.long	0
	.long	0
	.long	LC1167
	.long	0
	.long	456
	.long	1
	.long	34082818
	.long	0
	.long	0
	.long	LC1167
	.long	0
	.long	456
	.long	1
	.long	67637250
	.long	0
	.long	0
	.long	LC1168
	.long	50331648
	.long	456
	.long	1
	.long	8193
	.long	0
	.long	0
	.long	LC1169
	.long	16777216
	.long	456
	.long	1
	.long	1073750016
	.long	0
	.long	0
	.long	LC1169
	.long	16777216
	.long	456
	.long	1
	.long	8194
	.long	0
	.long	0
	.long	LC1170
	.long	16777216
	.long	456
	.long	1
	.long	8196
	.long	0
	.long	0
	.long	LC1171
	.long	50331648
	.long	456
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1172
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1173:
	.ascii "\322\1`\0"
	.data
	.align 32
_instrux_PUSHA:
	.long	457
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1173
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1174:
	.ascii "\321\1`\0"
	.data
	.align 32
_instrux_PUSHAD:
	.long	458
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1174
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1175:
	.ascii "\320\1`\0"
	.data
	.align 32
_instrux_PUSHAW:
	.long	459
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1175
	.long	16777216
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1176:
	.ascii "\322\1\234\0"
	.data
	.align 32
_instrux_PUSHF:
	.long	460
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1176
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1177:
	.ascii "\321\1\234\0"
	.data
	.align 32
_instrux_PUSHFD:
	.long	461
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1177
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1178:
	.ascii "\320\1\234\0"
	.data
	.align 32
_instrux_PUSHFW:
	.long	462
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1178
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1179:
	.ascii "\301\2\17\357H\0"
LC1180:
	.ascii "\2\17\357H\0"
LC1181:
	.ascii "\301\3f\17\357H\0"
LC1182:
	.ascii "\3f\17\357H\0"
	.data
	.align 32
_instrux_PXOR:
	.long	463
	.long	2
	.long	2101256
	.long	2113536
	.long	0
	.long	LC1179
	.long	83902465
	.long	463
	.long	2
	.long	2101256
	.long	2101256
	.long	0
	.long	LC1180
	.long	83902464
	.long	463
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1181
	.long	134348801
	.long	463
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1182
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1183:
	.ascii "\300\1\320\202\0"
LC1184:
	.ascii "\300\1\322\202\0"
LC1185:
	.ascii "\300\1\300\202\25\0"
LC1186:
	.ascii "\320\300\1\321\202\0"
LC1187:
	.ascii "\320\300\1\323\202\0"
LC1188:
	.ascii "\320\300\1\301\202\25\0"
LC1189:
	.ascii "\321\300\1\321\202\0"
LC1190:
	.ascii "\321\300\1\323\202\0"
LC1191:
	.ascii "\321\300\1\301\202\25\0"
	.data
	.align 32
_instrux_RCL:
	.long	464
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1183
	.long	0
	.long	464
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1184
	.long	0
	.long	464
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1185
	.long	16777220
	.long	464
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1186
	.long	0
	.long	464
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1187
	.long	0
	.long	464
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1188
	.long	16777220
	.long	464
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1189
	.long	50331648
	.long	464
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1190
	.long	50331648
	.long	464
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1191
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1192:
	.ascii "\301\331\2\17SH\0"
LC1193:
	.ascii "\331\2\17SH\0"
	.data
	.align 32
_instrux_RCPPS:
	.long	465
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1192
	.long	117506048
	.long	465
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1193
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1194:
	.ascii "\301\333\2\17SH\0"
LC1195:
	.ascii "\333\2\17SH\0"
	.data
	.align 32
_instrux_RCPSS:
	.long	466
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1194
	.long	117506048
	.long	466
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1195
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1196:
	.ascii "\300\1\320\203\0"
LC1197:
	.ascii "\300\1\322\203\0"
LC1198:
	.ascii "\300\1\300\203\25\0"
LC1199:
	.ascii "\320\300\1\321\203\0"
LC1200:
	.ascii "\320\300\1\323\203\0"
LC1201:
	.ascii "\320\300\1\301\203\25\0"
LC1202:
	.ascii "\321\300\1\321\203\0"
LC1203:
	.ascii "\321\300\1\323\203\0"
LC1204:
	.ascii "\321\300\1\301\203\25\0"
	.data
	.align 32
_instrux_RCR:
	.long	467
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1196
	.long	0
	.long	467
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1197
	.long	0
	.long	467
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1198
	.long	16777220
	.long	467
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1199
	.long	0
	.long	467
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1200
	.long	0
	.long	467
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1201
	.long	16777220
	.long	467
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1202
	.long	50331648
	.long	467
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1203
	.long	50331648
	.long	467
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1204
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1205:
	.ascii "\2\17"
	.ascii "2\0"
	.data
	.align 32
_instrux_RDMSR:
	.long	468
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1205
	.long	83886336
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1206:
	.ascii "\2\17"
	.ascii "3\0"
	.data
	.align 32
_instrux_RDPMC:
	.long	469
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1206
	.long	100663296
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1207:
	.ascii "\321\300\2\17"
	.ascii "6\200\0"
	.data
	.align 32
_instrux_RDSHR:
	.long	470
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC1207
	.long	369099264
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1208:
	.ascii "\2\17"
	.ascii "1\0"
	.data
	.align 32
_instrux_RDTSC:
	.long	471
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1208
	.long	83886080
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1209:
	.ascii "\340\0"
	.data
	.align 32
_instrux_RESB:
	.long	472
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1209
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_RESD:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_RESQ:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_REST:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 4
_instrux_RESW:
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1210:
	.ascii "\1\303\0"
LC1211:
	.ascii "\1\302\30\0"
	.data
	.align 32
_instrux_RET:
	.long	477
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1210
	.long	0
	.long	477
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1211
	.long	8
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1212:
	.ascii "\1\313\0"
LC1213:
	.ascii "\1\312\30\0"
	.data
	.align 32
_instrux_RETF:
	.long	478
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1212
	.long	0
	.long	478
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1213
	.long	8
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_RETN:
	.long	479
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1210
	.long	0
	.long	479
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1211
	.long	8
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1214:
	.ascii "\300\1\320\200\0"
LC1215:
	.ascii "\300\1\322\200\0"
LC1216:
	.ascii "\300\1\300\200\25\0"
LC1217:
	.ascii "\320\300\1\321\200\0"
LC1218:
	.ascii "\320\300\1\323\200\0"
LC1219:
	.ascii "\320\300\1\301\200\25\0"
LC1220:
	.ascii "\321\300\1\321\200\0"
LC1221:
	.ascii "\321\300\1\323\200\0"
LC1222:
	.ascii "\321\300\1\301\200\25\0"
	.data
	.align 32
_instrux_ROL:
	.long	480
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1214
	.long	0
	.long	480
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1215
	.long	0
	.long	480
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1216
	.long	16777220
	.long	480
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1217
	.long	0
	.long	480
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1218
	.long	0
	.long	480
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1219
	.long	16777220
	.long	480
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1220
	.long	50331648
	.long	480
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1221
	.long	50331648
	.long	480
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1222
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1223:
	.ascii "\300\1\320\201\0"
LC1224:
	.ascii "\300\1\322\201\0"
LC1225:
	.ascii "\300\1\300\201\25\0"
LC1226:
	.ascii "\320\300\1\321\201\0"
LC1227:
	.ascii "\320\300\1\323\201\0"
LC1228:
	.ascii "\320\300\1\301\201\25\0"
LC1229:
	.ascii "\321\300\1\321\201\0"
LC1230:
	.ascii "\321\300\1\323\201\0"
LC1231:
	.ascii "\321\300\1\301\201\25\0"
	.data
	.align 32
_instrux_ROR:
	.long	481
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1223
	.long	0
	.long	481
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1224
	.long	0
	.long	481
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1225
	.long	16777220
	.long	481
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1226
	.long	0
	.long	481
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1227
	.long	0
	.long	481
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1228
	.long	16777220
	.long	481
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1229
	.long	50331648
	.long	481
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1230
	.long	50331648
	.long	481
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1231
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1232:
	.ascii "\301\2\17yH\0"
	.data
	.align 32
_instrux_RSDC:
	.long	482
	.long	2
	.long	528386
	.long	2113552
	.long	0
	.long	LC1232
	.long	335544832
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1233:
	.ascii "\300\2\17{\200\0"
	.data
	.align 32
_instrux_RSLDT:
	.long	483
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC1233
	.long	335544832
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1234:
	.ascii "\2\17\252\0"
	.data
	.align 32
_instrux_RSM:
	.long	484
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1234
	.long	83886592
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1235:
	.ascii "\301\331\2\17RH\0"
LC1236:
	.ascii "\331\2\17RH\0"
	.data
	.align 32
_instrux_RSQRTPS:
	.long	485
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1235
	.long	117506048
	.long	485
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1236
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1237:
	.ascii "\301\333\2\17RH\0"
LC1238:
	.ascii "\333\2\17RH\0"
	.data
	.align 32
_instrux_RSQRTSS:
	.long	486
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1237
	.long	117506048
	.long	486
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1238
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1239:
	.ascii "\300\2\17}\200\0"
	.data
	.align 32
_instrux_RSTS:
	.long	487
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC1239
	.long	335544832
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1240:
	.ascii "\1\236\0"
	.data
	.align 32
_instrux_SAHF:
	.long	488
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1240
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1241:
	.ascii "\300\1\320\204\0"
LC1242:
	.ascii "\300\1\322\204\0"
LC1243:
	.ascii "\300\1\300\204\25\0"
LC1244:
	.ascii "\320\300\1\321\204\0"
LC1245:
	.ascii "\320\300\1\323\204\0"
LC1246:
	.ascii "\320\300\1\301\204\25\0"
LC1247:
	.ascii "\321\300\1\321\204\0"
LC1248:
	.ascii "\321\300\1\323\204\0"
LC1249:
	.ascii "\321\300\1\301\204\25\0"
	.data
	.align 32
_instrux_SAL:
	.long	489
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1241
	.long	0
	.long	489
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1242
	.long	0
	.long	489
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1243
	.long	16777220
	.long	489
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1244
	.long	0
	.long	489
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1245
	.long	0
	.long	489
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1246
	.long	16777220
	.long	489
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1247
	.long	50331648
	.long	489
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1248
	.long	50331648
	.long	489
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1249
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1250:
	.ascii "\1\326\0"
	.data
	.align 32
_instrux_SALC:
	.long	490
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1250
	.long	4096
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1251:
	.ascii "\300\1\320\207\0"
LC1252:
	.ascii "\300\1\322\207\0"
LC1253:
	.ascii "\300\1\300\207\25\0"
LC1254:
	.ascii "\320\300\1\321\207\0"
LC1255:
	.ascii "\320\300\1\323\207\0"
LC1256:
	.ascii "\320\300\1\301\207\25\0"
LC1257:
	.ascii "\321\300\1\321\207\0"
LC1258:
	.ascii "\321\300\1\323\207\0"
LC1259:
	.ascii "\321\300\1\301\207\25\0"
	.data
	.align 32
_instrux_SAR:
	.long	491
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1251
	.long	0
	.long	491
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1252
	.long	0
	.long	491
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1253
	.long	16777220
	.long	491
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1254
	.long	0
	.long	491
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1255
	.long	0
	.long	491
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1256
	.long	16777220
	.long	491
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1257
	.long	50331648
	.long	491
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1258
	.long	50331648
	.long	491
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1259
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1260:
	.ascii "\300\1\30A\0"
LC1261:
	.ascii "\1\30A\0"
LC1262:
	.ascii "\320\300\1\31A\0"
LC1263:
	.ascii "\320\1\31A\0"
LC1264:
	.ascii "\321\300\1\31A\0"
LC1265:
	.ascii "\321\1\31A\0"
LC1266:
	.ascii "\301\1\32H\0"
LC1267:
	.ascii "\1\32H\0"
LC1268:
	.ascii "\320\301\1\33H\0"
LC1269:
	.ascii "\320\1\33H\0"
LC1270:
	.ascii "\321\301\1\33H\0"
LC1271:
	.ascii "\321\1\33H\0"
LC1272:
	.ascii "\320\300\1\203\203\15\0"
LC1273:
	.ascii "\321\300\1\203\203\15\0"
LC1274:
	.ascii "\1\34\21\0"
LC1275:
	.ascii "\320\1\203\203\15\0"
LC1276:
	.ascii "\320\1\35\31\0"
LC1277:
	.ascii "\321\1\203\203\15\0"
LC1278:
	.ascii "\321\1\35!\0"
LC1279:
	.ascii "\300\1\200\203\21\0"
LC1280:
	.ascii "\320\300\\\1\201\203Y\0"
LC1281:
	.ascii "\321\300d\1\201\203a\0"
	.data
	.align 32
_instrux_SBB:
	.long	492
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1260
	.long	1
	.long	492
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1261
	.long	0
	.long	492
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1262
	.long	1
	.long	492
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1263
	.long	0
	.long	492
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1264
	.long	50331649
	.long	492
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1265
	.long	50331648
	.long	492
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC1266
	.long	1
	.long	492
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1267
	.long	0
	.long	492
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1268
	.long	1
	.long	492
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1269
	.long	0
	.long	492
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1270
	.long	50331649
	.long	492
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1271
	.long	50331648
	.long	492
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC1272
	.long	0
	.long	492
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC1273
	.long	50331648
	.long	492
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC1274
	.long	1
	.long	492
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC1275
	.long	1
	.long	492
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC1276
	.long	1
	.long	492
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC1277
	.long	50331649
	.long	492
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC1278
	.long	50331649
	.long	492
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1279
	.long	1
	.long	492
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1280
	.long	1
	.long	492
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1281
	.long	50331649
	.long	492
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC1279
	.long	1
	.long	492
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC1280
	.long	1
	.long	492
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC1281
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1282:
	.ascii "\332\1\256\0"
	.data
	.align 32
_instrux_SCASB:
	.long	493
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1282
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1283:
	.ascii "\332\321\1\257\0"
	.data
	.align 32
_instrux_SCASD:
	.long	494
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1283
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1284:
	.ascii "\332\320\1\257\0"
	.data
	.align 32
_instrux_SCASW:
	.long	495
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1284
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1285:
	.ascii "\3\17\256\370\0"
	.data
	.align 32
_instrux_SFENCE:
	.long	496
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1285
	.long	117440512
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1286:
	.ascii "\300\2\17\1\200\0"
	.data
	.align 32
_instrux_SGDT:
	.long	497
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1286
	.long	33554432
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_SHL:
	.long	498
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1241
	.long	0
	.long	498
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1242
	.long	0
	.long	498
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1243
	.long	16777220
	.long	498
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1244
	.long	0
	.long	498
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1245
	.long	0
	.long	498
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1246
	.long	16777220
	.long	498
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1247
	.long	50331648
	.long	498
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1248
	.long	50331648
	.long	498
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1249
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1287:
	.ascii "\300\320\2\17\244A\26\0"
LC1288:
	.ascii "\320\2\17\244A\26\0"
LC1289:
	.ascii "\300\321\2\17\244A\26\0"
LC1290:
	.ascii "\321\2\17\244A\26\0"
LC1291:
	.ascii "\300\320\2\17\245A\0"
LC1292:
	.ascii "\320\2\17\245A\0"
LC1293:
	.ascii "\300\321\2\17\245A\0"
LC1294:
	.ascii "\321\2\17\245A\0"
	.data
	.align 32
_instrux_SHLD:
	.long	499
	.long	3
	.long	2113536
	.long	2101250
	.long	8192
	.long	LC1287
	.long	50331750
	.long	499
	.long	3
	.long	2101250
	.long	2101250
	.long	8192
	.long	LC1288
	.long	50331750
	.long	499
	.long	3
	.long	2113536
	.long	2101252
	.long	8192
	.long	LC1289
	.long	50331750
	.long	499
	.long	3
	.long	2101252
	.long	2101252
	.long	8192
	.long	LC1290
	.long	50331750
	.long	499
	.long	3
	.long	2113536
	.long	2101250
	.long	2232321
	.long	LC1291
	.long	50331649
	.long	499
	.long	3
	.long	2101250
	.long	2101250
	.long	2232321
	.long	LC1292
	.long	50331648
	.long	499
	.long	3
	.long	2113536
	.long	2101252
	.long	2232321
	.long	LC1293
	.long	50331649
	.long	499
	.long	3
	.long	2101252
	.long	2101252
	.long	2232321
	.long	LC1294
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1295:
	.ascii "\300\1\320\205\0"
LC1296:
	.ascii "\300\1\322\205\0"
LC1297:
	.ascii "\300\1\300\205\25\0"
LC1298:
	.ascii "\320\300\1\321\205\0"
LC1299:
	.ascii "\320\300\1\323\205\0"
LC1300:
	.ascii "\320\300\1\301\205\25\0"
LC1301:
	.ascii "\321\300\1\321\205\0"
LC1302:
	.ascii "\321\300\1\323\205\0"
LC1303:
	.ascii "\321\300\1\301\205\25\0"
	.data
	.align 32
_instrux_SHR:
	.long	500
	.long	2
	.long	2097153
	.long	8396800
	.long	0
	.long	LC1295
	.long	0
	.long	500
	.long	2
	.long	2097153
	.long	2232321
	.long	0
	.long	LC1296
	.long	0
	.long	500
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1297
	.long	16777220
	.long	500
	.long	2
	.long	2097154
	.long	8396800
	.long	0
	.long	LC1298
	.long	0
	.long	500
	.long	2
	.long	2097154
	.long	2232321
	.long	0
	.long	LC1299
	.long	0
	.long	500
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1300
	.long	16777220
	.long	500
	.long	2
	.long	2097156
	.long	8396800
	.long	0
	.long	LC1301
	.long	50331648
	.long	500
	.long	2
	.long	2097156
	.long	2232321
	.long	0
	.long	LC1302
	.long	50331648
	.long	500
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1303
	.long	50331652
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1304:
	.ascii "\300\320\2\17\254A\26\0"
LC1305:
	.ascii "\320\2\17\254A\26\0"
LC1306:
	.ascii "\300\321\2\17\254A\26\0"
LC1307:
	.ascii "\321\2\17\254A\26\0"
LC1308:
	.ascii "\300\320\2\17\255A\0"
LC1309:
	.ascii "\320\2\17\255A\0"
LC1310:
	.ascii "\300\321\2\17\255A\0"
LC1311:
	.ascii "\321\2\17\255A\0"
	.data
	.align 32
_instrux_SHRD:
	.long	501
	.long	3
	.long	2113536
	.long	2101250
	.long	8192
	.long	LC1304
	.long	50331750
	.long	501
	.long	3
	.long	2101250
	.long	2101250
	.long	8192
	.long	LC1305
	.long	50331750
	.long	501
	.long	3
	.long	2113536
	.long	2101252
	.long	8192
	.long	LC1306
	.long	50331750
	.long	501
	.long	3
	.long	2101252
	.long	2101252
	.long	8192
	.long	LC1307
	.long	50331750
	.long	501
	.long	3
	.long	2113536
	.long	2101250
	.long	2232321
	.long	LC1308
	.long	50331649
	.long	501
	.long	3
	.long	2101250
	.long	2101250
	.long	2232321
	.long	LC1309
	.long	50331648
	.long	501
	.long	3
	.long	2113536
	.long	2101252
	.long	2232321
	.long	LC1310
	.long	50331649
	.long	501
	.long	3
	.long	2101252
	.long	2101252
	.long	2232321
	.long	LC1311
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1312:
	.ascii "\3f\17\306H\26\0"
LC1313:
	.ascii "\301\3f\17\306H\26\0"
	.data
	.align 32
_instrux_SHUFPD:
	.long	502
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC1312
	.long	134348900
	.long	502
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC1313
	.long	134348901
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1314:
	.ascii "\301\2\17\306H\26\0"
LC1315:
	.ascii "\2\17\306H\26\0"
	.data
	.align 32
_instrux_SHUFPS:
	.long	503
	.long	3
	.long	2101264
	.long	2113536
	.long	8192
	.long	LC1314
	.long	117506148
	.long	503
	.long	3
	.long	2101264
	.long	2101264
	.long	8192
	.long	LC1315
	.long	117506148
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1316:
	.ascii "\300\2\17\1\201\0"
	.data
	.align 32
_instrux_SIDT:
	.long	504
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1316
	.long	33554432
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1317:
	.ascii "\300\1\17\17\200\0"
LC1318:
	.ascii "\320\1\17\17\200\0"
LC1319:
	.ascii "\321\1\17\17\200\0"
	.data
	.align 32
_instrux_SLDT:
	.long	505
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1317
	.long	33554432
	.long	505
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC1317
	.long	33554432
	.long	505
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1318
	.long	33554432
	.long	505
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC1319
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_SMI:
	.long	506
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC516
	.long	50335744
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1320:
	.ascii "\2\17"
	.ascii "8\0"
	.data
	.align 32
_instrux_SMINT:
	.long	507
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1320
	.long	369098752
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1321:
	.ascii "\2\17~\0"
	.data
	.align 32
_instrux_SMINTOLD:
	.long	508
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1321
	.long	335544320
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1322:
	.ascii "\300\2\17\1\204\0"
LC1323:
	.ascii "\320\2\17\1\204\0"
LC1324:
	.ascii "\321\2\17\1\204\0"
	.data
	.align 32
_instrux_SMSW:
	.long	509
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1322
	.long	33554432
	.long	509
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC1322
	.long	33554432
	.long	509
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1323
	.long	33554432
	.long	509
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC1324
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1325:
	.ascii "\3f\17QH\0"
LC1326:
	.ascii "\301\3f\17QH\0"
	.data
	.align 32
_instrux_SQRTPD:
	.long	510
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1325
	.long	134348800
	.long	510
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1326
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1327:
	.ascii "\301\331\2\17QH\0"
LC1328:
	.ascii "\331\2\17QH\0"
	.data
	.align 32
_instrux_SQRTPS:
	.long	511
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1327
	.long	117506048
	.long	511
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1328
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1329:
	.ascii "\3\362\17QH\0"
LC1330:
	.ascii "\301\3\362\17QH\0"
	.data
	.align 32
_instrux_SQRTSD:
	.long	512
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1329
	.long	134348800
	.long	512
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1330
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1331:
	.ascii "\301\333\2\17QH\0"
LC1332:
	.ascii "\333\2\17QH\0"
	.data
	.align 32
_instrux_SQRTSS:
	.long	513
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1331
	.long	117506048
	.long	513
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1332
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1333:
	.ascii "\1\371\0"
	.data
	.align 32
_instrux_STC:
	.long	514
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1333
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1334:
	.ascii "\1\375\0"
	.data
	.align 32
_instrux_STD:
	.long	515
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1334
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1335:
	.ascii "\1\373\0"
	.data
	.align 32
_instrux_STI:
	.long	516
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1335
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1336:
	.ascii "\300\2\17\256\203\0"
	.data
	.align 32
_instrux_STMXCSR:
	.long	517
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1336
	.long	117506064
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1337:
	.ascii "\1\252\0"
	.data
	.align 32
_instrux_STOSB:
	.long	518
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1337
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1338:
	.ascii "\321\1\253\0"
	.data
	.align 32
_instrux_STOSD:
	.long	519
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1338
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1339:
	.ascii "\320\1\253\0"
	.data
	.align 32
_instrux_STOSW:
	.long	520
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1339
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1340:
	.ascii "\300\1\17\17\201\0"
LC1341:
	.ascii "\320\1\17\17\201\0"
LC1342:
	.ascii "\321\1\17\17\201\0"
	.data
	.align 32
_instrux_STR:
	.long	521
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1340
	.long	33555456
	.long	521
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC1340
	.long	33555456
	.long	521
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1341
	.long	33555456
	.long	521
	.long	1
	.long	2101252
	.long	0
	.long	0
	.long	LC1342
	.long	50332672
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1343:
	.ascii "\300\1(A\0"
LC1344:
	.ascii "\1(A\0"
LC1345:
	.ascii "\320\300\1)A\0"
LC1346:
	.ascii "\320\1)A\0"
LC1347:
	.ascii "\321\300\1)A\0"
LC1348:
	.ascii "\321\1)A\0"
LC1349:
	.ascii "\301\1*H\0"
LC1350:
	.ascii "\1*H\0"
LC1351:
	.ascii "\320\301\1+H\0"
LC1352:
	.ascii "\320\1+H\0"
LC1353:
	.ascii "\321\301\1+H\0"
LC1354:
	.ascii "\321\1+H\0"
LC1355:
	.ascii "\320\300\1\203\205\15\0"
LC1356:
	.ascii "\321\300\1\203\205\15\0"
LC1357:
	.ascii "\1,\21\0"
LC1358:
	.ascii "\320\1\203\205\15\0"
LC1359:
	.ascii "\320\1-\31\0"
LC1360:
	.ascii "\321\1\203\205\15\0"
LC1361:
	.ascii "\321\1-!\0"
LC1362:
	.ascii "\300\1\200\205\21\0"
LC1363:
	.ascii "\320\300\\\1\201\205Y\0"
LC1364:
	.ascii "\321\300d\1\201\205a\0"
	.data
	.align 32
_instrux_SUB:
	.long	522
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1343
	.long	1
	.long	522
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1344
	.long	0
	.long	522
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1345
	.long	1
	.long	522
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1346
	.long	0
	.long	522
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1347
	.long	50331649
	.long	522
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1348
	.long	50331648
	.long	522
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC1349
	.long	1
	.long	522
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1350
	.long	0
	.long	522
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1351
	.long	1
	.long	522
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1352
	.long	0
	.long	522
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1353
	.long	50331649
	.long	522
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1354
	.long	50331648
	.long	522
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC1355
	.long	0
	.long	522
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC1356
	.long	50331648
	.long	522
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC1357
	.long	1
	.long	522
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC1358
	.long	1
	.long	522
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC1359
	.long	1
	.long	522
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC1360
	.long	50331649
	.long	522
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC1361
	.long	50331649
	.long	522
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1362
	.long	1
	.long	522
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1363
	.long	1
	.long	522
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1364
	.long	50331649
	.long	522
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC1362
	.long	1
	.long	522
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC1363
	.long	1
	.long	522
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC1364
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1365:
	.ascii "\3f\17\\H\0"
LC1366:
	.ascii "\301\3f\17\\H\0"
	.data
	.align 32
_instrux_SUBPD:
	.long	523
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1365
	.long	134348800
	.long	523
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1366
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1367:
	.ascii "\301\331\2\17\\H\0"
LC1368:
	.ascii "\331\2\17\\H\0"
	.data
	.align 32
_instrux_SUBPS:
	.long	524
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1367
	.long	117506048
	.long	524
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1368
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1369:
	.ascii "\3\362\17\\H\0"
LC1370:
	.ascii "\301\3\362\17\\H\0"
	.data
	.align 32
_instrux_SUBSD:
	.long	525
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1369
	.long	134348800
	.long	525
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1370
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1371:
	.ascii "\301\333\2\17\\H\0"
LC1372:
	.ascii "\333\2\17\\H\0"
	.data
	.align 32
_instrux_SUBSS:
	.long	526
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1371
	.long	117506048
	.long	526
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1372
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1373:
	.ascii "\300\2\17xA\0"
	.data
	.align 32
_instrux_SVDC:
	.long	527
	.long	2
	.long	2113552
	.long	528386
	.long	0
	.long	LC1373
	.long	335544832
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1374:
	.ascii "\300\2\17z\200\0"
	.data
	.align 32
_instrux_SVLDT:
	.long	528
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC1374
	.long	335544832
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1375:
	.ascii "\300\2\17|\200\0"
	.data
	.align 32
_instrux_SVTS:
	.long	529
	.long	1
	.long	2113552
	.long	0
	.long	0
	.long	LC1375
	.long	335544832
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_SYSCALL:
	.long	530
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC617
	.long	637534208
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1376:
	.ascii "\2\17"
	.ascii "4\0"
	.data
	.align 32
_instrux_SYSENTER:
	.long	531
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1376
	.long	100663296
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1377:
	.ascii "\2\17"
	.ascii "5\0"
	.data
	.align 32
_instrux_SYSEXIT:
	.long	532
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1377
	.long	100663552
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_SYSRET:
	.long	533
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC616
	.long	637534464
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1378:
	.ascii "\300\1\204A\0"
LC1379:
	.ascii "\1\204A\0"
LC1380:
	.ascii "\320\300\1\205A\0"
LC1381:
	.ascii "\320\1\205A\0"
LC1382:
	.ascii "\321\300\1\205A\0"
LC1383:
	.ascii "\321\1\205A\0"
LC1384:
	.ascii "\301\1\204H\0"
LC1385:
	.ascii "\320\301\1\205H\0"
LC1386:
	.ascii "\321\301\1\205H\0"
LC1387:
	.ascii "\1\250\21\0"
LC1388:
	.ascii "\320\1\251\31\0"
LC1389:
	.ascii "\321\1\251!\0"
LC1390:
	.ascii "\300\1\366\200\21\0"
LC1391:
	.ascii "\320\300\1\367\200\31\0"
LC1392:
	.ascii "\321\300\1\367\200!\0"
	.data
	.align 32
_instrux_TEST:
	.long	534
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1378
	.long	1
	.long	534
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1379
	.long	0
	.long	534
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1380
	.long	1
	.long	534
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1381
	.long	0
	.long	534
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1382
	.long	50331649
	.long	534
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1383
	.long	50331648
	.long	534
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC1384
	.long	1
	.long	534
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1385
	.long	1
	.long	534
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1386
	.long	50331649
	.long	534
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC1387
	.long	1
	.long	534
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC1388
	.long	1
	.long	534
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC1389
	.long	50331649
	.long	534
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1390
	.long	1
	.long	534
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1391
	.long	1
	.long	534
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1392
	.long	50331649
	.long	534
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC1390
	.long	1
	.long	534
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC1391
	.long	1
	.long	534
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC1392
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1393:
	.ascii "\3f\17.H\0"
LC1394:
	.ascii "\301\3f\17.H\0"
	.data
	.align 32
_instrux_UCOMISD:
	.long	535
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1393
	.long	134348800
	.long	535
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1394
	.long	134348800
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1395:
	.ascii "\301\2\17.H\0"
LC1396:
	.ascii "\2\17.H\0"
	.data
	.align 32
_instrux_UCOMISS:
	.long	536
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1395
	.long	117506048
	.long	536
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1396
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1397:
	.ascii "\2\17\377\0"
	.data
	.align 32
_instrux_UD0:
	.long	537
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1397
	.long	33558528
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1398:
	.ascii "\2\17\271\0"
	.data
	.align 32
_instrux_UD1:
	.long	538
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1398
	.long	33558528
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1399:
	.ascii "\2\17\13\0"
	.data
	.align 32
_instrux_UD2:
	.long	539
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1399
	.long	33554432
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1400:
	.ascii "\300\2\17\20A\0"
LC1401:
	.ascii "\2\17\20A\0"
LC1402:
	.ascii "\320\300\2\17\21A\0"
LC1403:
	.ascii "\320\2\17\21A\0"
LC1404:
	.ascii "\321\300\2\17\21A\0"
LC1405:
	.ascii "\321\2\17\21A\0"
LC1406:
	.ascii "\320\301\2\17\23H\0"
LC1407:
	.ascii "\320\2\17\23H\0"
LC1408:
	.ascii "\321\301\2\17\23H\0"
LC1409:
	.ascii "\321\2\17\23H\0"
	.data
	.align 32
_instrux_UMOV:
	.long	540
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1400
	.long	50335745
	.long	540
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1401
	.long	50335744
	.long	540
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1402
	.long	50335745
	.long	540
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1403
	.long	50335744
	.long	540
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1404
	.long	50335745
	.long	540
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1405
	.long	50335744
	.long	540
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC728
	.long	50335745
	.long	540
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC720
	.long	50335744
	.long	540
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1406
	.long	50335745
	.long	540
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1407
	.long	50335744
	.long	540
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1408
	.long	50335745
	.long	540
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1409
	.long	50335744
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1410:
	.ascii "\3f\17\25H\0"
LC1411:
	.ascii "\301\3f\17\25H\0"
	.data
	.align 32
_instrux_UNPCKHPD:
	.long	541
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1410
	.long	134348800
	.long	541
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1411
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1412:
	.ascii "\301\2\17\25H\0"
LC1413:
	.ascii "\2\17\25H\0"
	.data
	.align 32
_instrux_UNPCKHPS:
	.long	542
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1412
	.long	117506048
	.long	542
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1413
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1414:
	.ascii "\3f\17\24H\0"
LC1415:
	.ascii "\301\3f\17\24H\0"
	.data
	.align 32
_instrux_UNPCKLPD:
	.long	543
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1414
	.long	134348800
	.long	543
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1415
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1416:
	.ascii "\301\2\17\24H\0"
LC1417:
	.ascii "\2\17\24H\0"
	.data
	.align 32
_instrux_UNPCKLPS:
	.long	544
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1416
	.long	117506048
	.long	544
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1417
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1418:
	.ascii "\300\1\17\17\204\0"
LC1419:
	.ascii "\1\17\17\204\0"
	.data
	.align 32
_instrux_VERR:
	.long	545
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1418
	.long	33555456
	.long	545
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC1418
	.long	33555456
	.long	545
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1419
	.long	33555456
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1420:
	.ascii "\300\1\17\17\205\0"
LC1421:
	.ascii "\1\17\17\205\0"
	.data
	.align 32
_instrux_VERW:
	.long	546
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1420
	.long	33555456
	.long	546
	.long	1
	.long	2113538
	.long	0
	.long	0
	.long	LC1420
	.long	33555456
	.long	546
	.long	1
	.long	2101250
	.long	0
	.long	0
	.long	LC1421
	.long	33555456
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_WAIT:
	.long	547
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC497
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1422:
	.ascii "\2\17\11\0"
	.data
	.align 32
_instrux_WBINVD:
	.long	548
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1422
	.long	67109120
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1423:
	.ascii "\2\17"
	.ascii "0\0"
	.data
	.align 32
_instrux_WRMSR:
	.long	549
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1423
	.long	83886336
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1424:
	.ascii "\321\300\2\17"
	.ascii "7\200\0"
	.data
	.align 32
_instrux_WRSHR:
	.long	550
	.long	1
	.long	2097156
	.long	0
	.long	0
	.long	LC1424
	.long	369099264
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1425:
	.ascii "\300\2\17\300A\0"
LC1426:
	.ascii "\2\17\300A\0"
LC1427:
	.ascii "\320\300\2\17\301A\0"
LC1428:
	.ascii "\320\2\17\301A\0"
LC1429:
	.ascii "\321\300\2\17\301A\0"
LC1430:
	.ascii "\321\2\17\301A\0"
	.data
	.align 32
_instrux_XADD:
	.long	551
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1425
	.long	67108865
	.long	551
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1426
	.long	67108864
	.long	551
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1427
	.long	67108865
	.long	551
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1428
	.long	67108864
	.long	551
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1429
	.long	67108865
	.long	551
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1430
	.long	67108864
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1431:
	.ascii "\320\301\2\17\246H\0"
LC1432:
	.ascii "\320\2\17\246H\0"
LC1433:
	.ascii "\321\301\2\17\246H\0"
LC1434:
	.ascii "\321\2\17\246H\0"
	.data
	.align 32
_instrux_XBTS:
	.long	552
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1431
	.long	50335752
	.long	552
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1432
	.long	50335744
	.long	552
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1433
	.long	50335760
	.long	552
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1434
	.long	50335744
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1435:
	.ascii "\320\11\220\0"
LC1436:
	.ascii "\321\11\220\0"
LC1437:
	.ascii "\320\10\220\0"
LC1438:
	.ascii "\321\10\220\0"
LC1439:
	.ascii "\301\1\206H\0"
LC1440:
	.ascii "\1\206H\0"
LC1441:
	.ascii "\320\301\1\207H\0"
LC1442:
	.ascii "\320\1\207H\0"
LC1443:
	.ascii "\321\301\1\207H\0"
LC1444:
	.ascii "\321\1\207H\0"
LC1445:
	.ascii "\300\1\206A\0"
LC1446:
	.ascii "\1\206A\0"
LC1447:
	.ascii "\320\300\1\207A\0"
LC1448:
	.ascii "\320\1\207A\0"
LC1449:
	.ascii "\321\300\1\207A\0"
LC1450:
	.ascii "\321\1\207A\0"
	.data
	.align 32
_instrux_XCHG:
	.long	553
	.long	2
	.long	2166786
	.long	2101250
	.long	0
	.long	LC1435
	.long	0
	.long	553
	.long	2
	.long	2166788
	.long	2101252
	.long	0
	.long	LC1436
	.long	50331648
	.long	553
	.long	2
	.long	2101250
	.long	2166786
	.long	0
	.long	LC1437
	.long	0
	.long	553
	.long	2
	.long	2101252
	.long	2166788
	.long	0
	.long	LC1438
	.long	50331648
	.long	553
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC1439
	.long	1
	.long	553
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1440
	.long	0
	.long	553
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1441
	.long	1
	.long	553
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1442
	.long	0
	.long	553
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1443
	.long	50331649
	.long	553
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1444
	.long	50331648
	.long	553
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1445
	.long	1
	.long	553
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1446
	.long	0
	.long	553
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1447
	.long	1
	.long	553
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1448
	.long	0
	.long	553
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1449
	.long	50331649
	.long	553
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1450
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1451:
	.ascii "\1\327\0"
	.data
	.align 32
_instrux_XLAT:
	.long	554
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1451
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.align 32
_instrux_XLATB:
	.long	555
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1451
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1452:
	.ascii "\300\1"
	.ascii "0A\0"
LC1453:
	.ascii "\1"
	.ascii "0A\0"
LC1454:
	.ascii "\320\300\1"
	.ascii "1A\0"
LC1455:
	.ascii "\320\1"
	.ascii "1A\0"
LC1456:
	.ascii "\321\300\1"
	.ascii "1A\0"
LC1457:
	.ascii "\321\1"
	.ascii "1A\0"
LC1458:
	.ascii "\301\1"
	.ascii "2H\0"
LC1459:
	.ascii "\1"
	.ascii "2H\0"
LC1460:
	.ascii "\320\301\1"
	.ascii "3H\0"
LC1461:
	.ascii "\320\1"
	.ascii "3H\0"
LC1462:
	.ascii "\321\301\1"
	.ascii "3H\0"
LC1463:
	.ascii "\321\1"
	.ascii "3H\0"
LC1464:
	.ascii "\320\300\1\203\206\15\0"
LC1465:
	.ascii "\321\300\1\203\206\15\0"
LC1466:
	.ascii "\1"
	.ascii "4\21\0"
LC1467:
	.ascii "\320\1\203\206\15\0"
LC1468:
	.ascii "\320\1"
	.ascii "5\31\0"
LC1469:
	.ascii "\321\1\203\206\15\0"
LC1470:
	.ascii "\321\1"
	.ascii "5!\0"
LC1471:
	.ascii "\300\1\200\206\21\0"
LC1472:
	.ascii "\320\300\\\1\201\206Y\0"
LC1473:
	.ascii "\321\300d\1\201\206a\0"
	.data
	.align 32
_instrux_XOR:
	.long	556
	.long	2
	.long	2113536
	.long	2101249
	.long	0
	.long	LC1452
	.long	1
	.long	556
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1453
	.long	0
	.long	556
	.long	2
	.long	2113536
	.long	2101250
	.long	0
	.long	LC1454
	.long	1
	.long	556
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1455
	.long	0
	.long	556
	.long	2
	.long	2113536
	.long	2101252
	.long	0
	.long	LC1456
	.long	50331649
	.long	556
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1457
	.long	50331648
	.long	556
	.long	2
	.long	2101249
	.long	2113536
	.long	0
	.long	LC1458
	.long	1
	.long	556
	.long	2
	.long	2101249
	.long	2101249
	.long	0
	.long	LC1459
	.long	0
	.long	556
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1460
	.long	1
	.long	556
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1461
	.long	0
	.long	556
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1462
	.long	50331649
	.long	556
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1463
	.long	50331648
	.long	556
	.long	2
	.long	2097154
	.long	8193
	.long	0
	.long	LC1464
	.long	0
	.long	556
	.long	2
	.long	2097156
	.long	8193
	.long	0
	.long	LC1465
	.long	50331648
	.long	556
	.long	2
	.long	2166785
	.long	8192
	.long	0
	.long	LC1466
	.long	1
	.long	556
	.long	2
	.long	2166786
	.long	1073750016
	.long	0
	.long	LC1467
	.long	1
	.long	556
	.long	2
	.long	2166786
	.long	8192
	.long	0
	.long	LC1468
	.long	1
	.long	556
	.long	2
	.long	2166788
	.long	1073750016
	.long	0
	.long	LC1469
	.long	50331649
	.long	556
	.long	2
	.long	2166788
	.long	8192
	.long	0
	.long	LC1470
	.long	50331649
	.long	556
	.long	2
	.long	2097153
	.long	8192
	.long	0
	.long	LC1471
	.long	1
	.long	556
	.long	2
	.long	2097154
	.long	8192
	.long	0
	.long	LC1472
	.long	1
	.long	556
	.long	2
	.long	2097156
	.long	8192
	.long	0
	.long	LC1473
	.long	50331649
	.long	556
	.long	2
	.long	2113536
	.long	8193
	.long	0
	.long	LC1471
	.long	1
	.long	556
	.long	2
	.long	2113536
	.long	8194
	.long	0
	.long	LC1472
	.long	1
	.long	556
	.long	2
	.long	2113536
	.long	8196
	.long	0
	.long	LC1473
	.long	50331649
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1474:
	.ascii "\3f\17WH\0"
LC1475:
	.ascii "\301\3f\17WH\0"
	.data
	.align 32
_instrux_XORPD:
	.long	557
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1474
	.long	134348800
	.long	557
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1475
	.long	134348801
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1476:
	.ascii "\301\2\17WH\0"
LC1477:
	.ascii "\2\17WH\0"
	.data
	.align 32
_instrux_XORPS:
	.long	558
	.long	2
	.long	2101264
	.long	2113536
	.long	0
	.long	LC1476
	.long	117506048
	.long	558
	.long	2
	.long	2101264
	.long	2101264
	.long	0
	.long	LC1477
	.long	117506048
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1478:
	.ascii "\3\17\247\300\0"
	.data
	.align 32
_instrux_XSTORE:
	.long	559
	.long	0
	.long	0
	.long	0
	.long	0
	.long	LC1478
	.long	369098752
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1479:
	.ascii "\320\301\1\17\330@H\0"
LC1480:
	.ascii "\320\1\17\330@H\0"
LC1481:
	.ascii "\321\301\1\17\330@H\0"
LC1482:
	.ascii "\321\1\17\330@H\0"
	.data
	.align 32
_instrux_CMOVcc:
	.long	560
	.long	2
	.long	2101250
	.long	2113536
	.long	0
	.long	LC1479
	.long	100663297
	.long	560
	.long	2
	.long	2101250
	.long	2101250
	.long	0
	.long	LC1480
	.long	100663296
	.long	560
	.long	2
	.long	2101252
	.long	2113536
	.long	0
	.long	LC1481
	.long	100663297
	.long	560
	.long	2
	.long	2101252
	.long	2101252
	.long	0
	.long	LC1482
	.long	100663296
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1483:
	.ascii "\322\1\17\330\200"
	.ascii "4\0"
LC1484:
	.ascii "\320\1\17\330\200"
	.ascii "4\0"
LC1485:
	.ascii "\321\1\17\330\200"
	.ascii "4\0"
LC1486:
	.ascii "\330p(\0"
LC1487:
	.ascii "\370\330p(\0"
LC1488:
	.ascii "\1\17\330\200"
	.ascii "4\0"
LC1489:
	.ascii "\330q\373\1\351"
	.ascii "4\0"
	.data
	.align 32
_instrux_Jcc:
	.long	561
	.long	1
	.long	8256
	.long	0
	.long	0
	.long	LC1483
	.long	50331648
	.long	561
	.long	1
	.long	8258
	.long	0
	.long	0
	.long	LC1484
	.long	50331648
	.long	561
	.long	1
	.long	8260
	.long	0
	.long	0
	.long	LC1485
	.long	50331648
	.long	561
	.long	1
	.long	8320
	.long	0
	.long	0
	.long	LC1486
	.long	0
	.long	561
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1487
	.long	0
	.long	561
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1488
	.long	50331648
	.long	561
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1489
	.long	0
	.long	561
	.long	1
	.long	8192
	.long	0
	.long	0
	.long	LC1486
	.long	0
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
	.text
LC1490:
	.ascii "\300\1\17\330\220\200\0"
	.data
	.align 32
_instrux_SETcc:
	.long	562
	.long	1
	.long	2113536
	.long	0
	.long	0
	.long	LC1490
	.long	50331652
	.long	562
	.long	1
	.long	2101249
	.long	0
	.long	0
	.long	LC1490
	.long	50331648
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	-1
	.long	0
	.long	0
.globl _nasm_instructions
	.align 32
_nasm_instructions:
	.long	_instrux_AAA
	.long	_instrux_AAD
	.long	_instrux_AAM
	.long	_instrux_AAS
	.long	_instrux_ADC
	.long	_instrux_ADD
	.long	_instrux_ADDPD
	.long	_instrux_ADDPS
	.long	_instrux_ADDSD
	.long	_instrux_ADDSS
	.long	_instrux_ADDSUBPD
	.long	_instrux_ADDSUBPS
	.long	_instrux_AND
	.long	_instrux_ANDNPD
	.long	_instrux_ANDNPS
	.long	_instrux_ANDPD
	.long	_instrux_ANDPS
	.long	_instrux_ARPL
	.long	_instrux_BOUND
	.long	_instrux_BSF
	.long	_instrux_BSR
	.long	_instrux_BSWAP
	.long	_instrux_BT
	.long	_instrux_BTC
	.long	_instrux_BTR
	.long	_instrux_BTS
	.long	_instrux_CALL
	.long	_instrux_CBW
	.long	_instrux_CDQ
	.long	_instrux_CLC
	.long	_instrux_CLD
	.long	_instrux_CLFLUSH
	.long	_instrux_CLI
	.long	_instrux_CLTS
	.long	_instrux_CMC
	.long	_instrux_CMP
	.long	_instrux_CMPEQPD
	.long	_instrux_CMPEQPS
	.long	_instrux_CMPEQSD
	.long	_instrux_CMPEQSS
	.long	_instrux_CMPLEPD
	.long	_instrux_CMPLEPS
	.long	_instrux_CMPLESD
	.long	_instrux_CMPLESS
	.long	_instrux_CMPLTPD
	.long	_instrux_CMPLTPS
	.long	_instrux_CMPLTSD
	.long	_instrux_CMPLTSS
	.long	_instrux_CMPNEQPD
	.long	_instrux_CMPNEQPS
	.long	_instrux_CMPNEQSD
	.long	_instrux_CMPNEQSS
	.long	_instrux_CMPNLEPD
	.long	_instrux_CMPNLEPS
	.long	_instrux_CMPNLESD
	.long	_instrux_CMPNLESS
	.long	_instrux_CMPNLTPD
	.long	_instrux_CMPNLTPS
	.long	_instrux_CMPNLTSD
	.long	_instrux_CMPNLTSS
	.long	_instrux_CMPORDPD
	.long	_instrux_CMPORDPS
	.long	_instrux_CMPORDSD
	.long	_instrux_CMPORDSS
	.long	_instrux_CMPPD
	.long	_instrux_CMPPS
	.long	_instrux_CMPSB
	.long	_instrux_CMPSD
	.long	_instrux_CMPSS
	.long	_instrux_CMPSW
	.long	_instrux_CMPUNORDPD
	.long	_instrux_CMPUNORDPS
	.long	_instrux_CMPUNORDSD
	.long	_instrux_CMPUNORDSS
	.long	_instrux_CMPXCHG
	.long	_instrux_CMPXCHG486
	.long	_instrux_CMPXCHG8B
	.long	_instrux_COMISD
	.long	_instrux_COMISS
	.long	_instrux_CPUID
	.long	_instrux_CVTDQ2PD
	.long	_instrux_CVTDQ2PS
	.long	_instrux_CVTPD2DQ
	.long	_instrux_CVTPD2PI
	.long	_instrux_CVTPD2PS
	.long	_instrux_CVTPI2PD
	.long	_instrux_CVTPI2PS
	.long	_instrux_CVTPS2DQ
	.long	_instrux_CVTPS2PD
	.long	_instrux_CVTPS2PI
	.long	_instrux_CVTSD2SI
	.long	_instrux_CVTSD2SS
	.long	_instrux_CVTSI2SD
	.long	_instrux_CVTSI2SS
	.long	_instrux_CVTSS2SD
	.long	_instrux_CVTSS2SI
	.long	_instrux_CVTTPD2DQ
	.long	_instrux_CVTTPD2PI
	.long	_instrux_CVTTPS2DQ
	.long	_instrux_CVTTPS2PI
	.long	_instrux_CVTTSD2SI
	.long	_instrux_CVTTSS2SI
	.long	_instrux_CWD
	.long	_instrux_CWDE
	.long	_instrux_DAA
	.long	_instrux_DAS
	.long	_instrux_DB
	.long	_instrux_DD
	.long	_instrux_DEC
	.long	_instrux_DIV
	.long	_instrux_DIVPD
	.long	_instrux_DIVPS
	.long	_instrux_DIVSD
	.long	_instrux_DIVSS
	.long	_instrux_DQ
	.long	_instrux_DT
	.long	_instrux_DW
	.long	_instrux_EMMS
	.long	_instrux_ENTER
	.long	_instrux_EQU
	.long	_instrux_F2XM1
	.long	_instrux_FABS
	.long	_instrux_FADD
	.long	_instrux_FADDP
	.long	_instrux_FBLD
	.long	_instrux_FBSTP
	.long	_instrux_FCHS
	.long	_instrux_FCLEX
	.long	_instrux_FCMOVB
	.long	_instrux_FCMOVBE
	.long	_instrux_FCMOVE
	.long	_instrux_FCMOVNB
	.long	_instrux_FCMOVNBE
	.long	_instrux_FCMOVNE
	.long	_instrux_FCMOVNU
	.long	_instrux_FCMOVU
	.long	_instrux_FCOM
	.long	_instrux_FCOMI
	.long	_instrux_FCOMIP
	.long	_instrux_FCOMP
	.long	_instrux_FCOMPP
	.long	_instrux_FCOS
	.long	_instrux_FDECSTP
	.long	_instrux_FDISI
	.long	_instrux_FDIV
	.long	_instrux_FDIVP
	.long	_instrux_FDIVR
	.long	_instrux_FDIVRP
	.long	_instrux_FEMMS
	.long	_instrux_FENI
	.long	_instrux_FFREE
	.long	_instrux_FFREEP
	.long	_instrux_FIADD
	.long	_instrux_FICOM
	.long	_instrux_FICOMP
	.long	_instrux_FIDIV
	.long	_instrux_FIDIVR
	.long	_instrux_FILD
	.long	_instrux_FIMUL
	.long	_instrux_FINCSTP
	.long	_instrux_FINIT
	.long	_instrux_FIST
	.long	_instrux_FISTP
	.long	_instrux_FISTTP
	.long	_instrux_FISUB
	.long	_instrux_FISUBR
	.long	_instrux_FLD
	.long	_instrux_FLD1
	.long	_instrux_FLDCW
	.long	_instrux_FLDENV
	.long	_instrux_FLDL2E
	.long	_instrux_FLDL2T
	.long	_instrux_FLDLG2
	.long	_instrux_FLDLN2
	.long	_instrux_FLDPI
	.long	_instrux_FLDZ
	.long	_instrux_FMUL
	.long	_instrux_FMULP
	.long	_instrux_FNCLEX
	.long	_instrux_FNDISI
	.long	_instrux_FNENI
	.long	_instrux_FNINIT
	.long	_instrux_FNOP
	.long	_instrux_FNSAVE
	.long	_instrux_FNSTCW
	.long	_instrux_FNSTENV
	.long	_instrux_FNSTSW
	.long	_instrux_FPATAN
	.long	_instrux_FPREM
	.long	_instrux_FPREM1
	.long	_instrux_FPTAN
	.long	_instrux_FRNDINT
	.long	_instrux_FRSTOR
	.long	_instrux_FSAVE
	.long	_instrux_FSCALE
	.long	_instrux_FSETPM
	.long	_instrux_FSIN
	.long	_instrux_FSINCOS
	.long	_instrux_FSQRT
	.long	_instrux_FST
	.long	_instrux_FSTCW
	.long	_instrux_FSTENV
	.long	_instrux_FSTP
	.long	_instrux_FSTSW
	.long	_instrux_FSUB
	.long	_instrux_FSUBP
	.long	_instrux_FSUBR
	.long	_instrux_FSUBRP
	.long	_instrux_FTST
	.long	_instrux_FUCOM
	.long	_instrux_FUCOMI
	.long	_instrux_FUCOMIP
	.long	_instrux_FUCOMP
	.long	_instrux_FUCOMPP
	.long	_instrux_FWAIT
	.long	_instrux_FXAM
	.long	_instrux_FXCH
	.long	_instrux_FXRSTOR
	.long	_instrux_FXSAVE
	.long	_instrux_FXTRACT
	.long	_instrux_FYL2X
	.long	_instrux_FYL2XP1
	.long	_instrux_HADDPD
	.long	_instrux_HADDPS
	.long	_instrux_HLT
	.long	_instrux_HSUBPD
	.long	_instrux_HSUBPS
	.long	_instrux_IBTS
	.long	_instrux_ICEBP
	.long	_instrux_IDIV
	.long	_instrux_IMUL
	.long	_instrux_IN
	.long	_instrux_INC
	.long	_instrux_INCBIN
	.long	_instrux_INSB
	.long	_instrux_INSD
	.long	_instrux_INSW
	.long	_instrux_INT
	.long	_instrux_INT01
	.long	_instrux_INT03
	.long	_instrux_INT1
	.long	_instrux_INT3
	.long	_instrux_INTO
	.long	_instrux_INVD
	.long	_instrux_INVLPG
	.long	_instrux_IRET
	.long	_instrux_IRETD
	.long	_instrux_IRETW
	.long	_instrux_JCXZ
	.long	_instrux_JECXZ
	.long	_instrux_JMP
	.long	_instrux_JMPE
	.long	_instrux_LAHF
	.long	_instrux_LAR
	.long	_instrux_LDDQU
	.long	_instrux_LDMXCSR
	.long	_instrux_LDS
	.long	_instrux_LEA
	.long	_instrux_LEAVE
	.long	_instrux_LES
	.long	_instrux_LFENCE
	.long	_instrux_LFS
	.long	_instrux_LGDT
	.long	_instrux_LGS
	.long	_instrux_LIDT
	.long	_instrux_LLDT
	.long	_instrux_LMSW
	.long	_instrux_LOADALL
	.long	_instrux_LOADALL286
	.long	_instrux_LODSB
	.long	_instrux_LODSD
	.long	_instrux_LODSW
	.long	_instrux_LOOP
	.long	_instrux_LOOPE
	.long	_instrux_LOOPNE
	.long	_instrux_LOOPNZ
	.long	_instrux_LOOPZ
	.long	_instrux_LSL
	.long	_instrux_LSS
	.long	_instrux_LTR
	.long	_instrux_MASKMOVDQU
	.long	_instrux_MASKMOVQ
	.long	_instrux_MAXPD
	.long	_instrux_MAXPS
	.long	_instrux_MAXSD
	.long	_instrux_MAXSS
	.long	_instrux_MFENCE
	.long	_instrux_MINPD
	.long	_instrux_MINPS
	.long	_instrux_MINSD
	.long	_instrux_MINSS
	.long	_instrux_MONITOR
	.long	_instrux_MOV
	.long	_instrux_MOVAPD
	.long	_instrux_MOVAPS
	.long	_instrux_MOVD
	.long	_instrux_MOVDDUP
	.long	_instrux_MOVDQ2Q
	.long	_instrux_MOVDQA
	.long	_instrux_MOVDQU
	.long	_instrux_MOVHLPS
	.long	_instrux_MOVHPD
	.long	_instrux_MOVHPS
	.long	_instrux_MOVLHPS
	.long	_instrux_MOVLPD
	.long	_instrux_MOVLPS
	.long	_instrux_MOVMSKPD
	.long	_instrux_MOVMSKPS
	.long	_instrux_MOVNTDQ
	.long	_instrux_MOVNTI
	.long	_instrux_MOVNTPD
	.long	_instrux_MOVNTPS
	.long	_instrux_MOVNTQ
	.long	_instrux_MOVQ
	.long	_instrux_MOVQ2DQ
	.long	_instrux_MOVSB
	.long	_instrux_MOVSD
	.long	_instrux_MOVSHDUP
	.long	_instrux_MOVSLDUP
	.long	_instrux_MOVSS
	.long	_instrux_MOVSW
	.long	_instrux_MOVSX
	.long	_instrux_MOVUPD
	.long	_instrux_MOVUPS
	.long	_instrux_MOVZX
	.long	_instrux_MUL
	.long	_instrux_MULPD
	.long	_instrux_MULPS
	.long	_instrux_MULSD
	.long	_instrux_MULSS
	.long	_instrux_MWAIT
	.long	_instrux_NEG
	.long	_instrux_NOP
	.long	_instrux_NOT
	.long	_instrux_OR
	.long	_instrux_ORPD
	.long	_instrux_ORPS
	.long	_instrux_OUT
	.long	_instrux_OUTSB
	.long	_instrux_OUTSD
	.long	_instrux_OUTSW
	.long	_instrux_PACKSSDW
	.long	_instrux_PACKSSWB
	.long	_instrux_PACKUSWB
	.long	_instrux_PADDB
	.long	_instrux_PADDD
	.long	_instrux_PADDQ
	.long	_instrux_PADDSB
	.long	_instrux_PADDSIW
	.long	_instrux_PADDSW
	.long	_instrux_PADDUSB
	.long	_instrux_PADDUSW
	.long	_instrux_PADDW
	.long	_instrux_PAND
	.long	_instrux_PANDN
	.long	_instrux_PAUSE
	.long	_instrux_PAVEB
	.long	_instrux_PAVGB
	.long	_instrux_PAVGUSB
	.long	_instrux_PAVGW
	.long	_instrux_PCMPEQB
	.long	_instrux_PCMPEQD
	.long	_instrux_PCMPEQW
	.long	_instrux_PCMPGTB
	.long	_instrux_PCMPGTD
	.long	_instrux_PCMPGTW
	.long	_instrux_PDISTIB
	.long	_instrux_PEXTRW
	.long	_instrux_PF2ID
	.long	_instrux_PF2IW
	.long	_instrux_PFACC
	.long	_instrux_PFADD
	.long	_instrux_PFCMPEQ
	.long	_instrux_PFCMPGE
	.long	_instrux_PFCMPGT
	.long	_instrux_PFMAX
	.long	_instrux_PFMIN
	.long	_instrux_PFMUL
	.long	_instrux_PFNACC
	.long	_instrux_PFPNACC
	.long	_instrux_PFRCP
	.long	_instrux_PFRCPIT1
	.long	_instrux_PFRCPIT2
	.long	_instrux_PFRSQIT1
	.long	_instrux_PFRSQRT
	.long	_instrux_PFSUB
	.long	_instrux_PFSUBR
	.long	_instrux_PI2FD
	.long	_instrux_PI2FW
	.long	_instrux_PINSRW
	.long	_instrux_PMACHRIW
	.long	_instrux_PMADDWD
	.long	_instrux_PMAGW
	.long	_instrux_PMAXSW
	.long	_instrux_PMAXUB
	.long	_instrux_PMINSW
	.long	_instrux_PMINUB
	.long	_instrux_PMOVMSKB
	.long	_instrux_PMULHRIW
	.long	_instrux_PMULHRWA
	.long	_instrux_PMULHRWC
	.long	_instrux_PMULHUW
	.long	_instrux_PMULHW
	.long	_instrux_PMULLW
	.long	_instrux_PMULUDQ
	.long	_instrux_PMVGEZB
	.long	_instrux_PMVLZB
	.long	_instrux_PMVNZB
	.long	_instrux_PMVZB
	.long	_instrux_POP
	.long	_instrux_POPA
	.long	_instrux_POPAD
	.long	_instrux_POPAW
	.long	_instrux_POPF
	.long	_instrux_POPFD
	.long	_instrux_POPFW
	.long	_instrux_POR
	.long	_instrux_PREFETCH
	.long	_instrux_PREFETCHNTA
	.long	_instrux_PREFETCHT0
	.long	_instrux_PREFETCHT1
	.long	_instrux_PREFETCHT2
	.long	_instrux_PREFETCHW
	.long	_instrux_PSADBW
	.long	_instrux_PSHUFD
	.long	_instrux_PSHUFHW
	.long	_instrux_PSHUFLW
	.long	_instrux_PSHUFW
	.long	_instrux_PSLLD
	.long	_instrux_PSLLDQ
	.long	_instrux_PSLLQ
	.long	_instrux_PSLLW
	.long	_instrux_PSRAD
	.long	_instrux_PSRAW
	.long	_instrux_PSRLD
	.long	_instrux_PSRLDQ
	.long	_instrux_PSRLQ
	.long	_instrux_PSRLW
	.long	_instrux_PSUBB
	.long	_instrux_PSUBD
	.long	_instrux_PSUBQ
	.long	_instrux_PSUBSB
	.long	_instrux_PSUBSIW
	.long	_instrux_PSUBSW
	.long	_instrux_PSUBUSB
	.long	_instrux_PSUBUSW
	.long	_instrux_PSUBW
	.long	_instrux_PSWAPD
	.long	_instrux_PUNPCKHBW
	.long	_instrux_PUNPCKHDQ
	.long	_instrux_PUNPCKHQDQ
	.long	_instrux_PUNPCKHWD
	.long	_instrux_PUNPCKLBW
	.long	_instrux_PUNPCKLDQ
	.long	_instrux_PUNPCKLQDQ
	.long	_instrux_PUNPCKLWD
	.long	_instrux_PUSH
	.long	_instrux_PUSHA
	.long	_instrux_PUSHAD
	.long	_instrux_PUSHAW
	.long	_instrux_PUSHF
	.long	_instrux_PUSHFD
	.long	_instrux_PUSHFW
	.long	_instrux_PXOR
	.long	_instrux_RCL
	.long	_instrux_RCPPS
	.long	_instrux_RCPSS
	.long	_instrux_RCR
	.long	_instrux_RDMSR
	.long	_instrux_RDPMC
	.long	_instrux_RDSHR
	.long	_instrux_RDTSC
	.long	_instrux_RESB
	.long	_instrux_RESD
	.long	_instrux_RESQ
	.long	_instrux_REST
	.long	_instrux_RESW
	.long	_instrux_RET
	.long	_instrux_RETF
	.long	_instrux_RETN
	.long	_instrux_ROL
	.long	_instrux_ROR
	.long	_instrux_RSDC
	.long	_instrux_RSLDT
	.long	_instrux_RSM
	.long	_instrux_RSQRTPS
	.long	_instrux_RSQRTSS
	.long	_instrux_RSTS
	.long	_instrux_SAHF
	.long	_instrux_SAL
	.long	_instrux_SALC
	.long	_instrux_SAR
	.long	_instrux_SBB
	.long	_instrux_SCASB
	.long	_instrux_SCASD
	.long	_instrux_SCASW
	.long	_instrux_SFENCE
	.long	_instrux_SGDT
	.long	_instrux_SHL
	.long	_instrux_SHLD
	.long	_instrux_SHR
	.long	_instrux_SHRD
	.long	_instrux_SHUFPD
	.long	_instrux_SHUFPS
	.long	_instrux_SIDT
	.long	_instrux_SLDT
	.long	_instrux_SMI
	.long	_instrux_SMINT
	.long	_instrux_SMINTOLD
	.long	_instrux_SMSW
	.long	_instrux_SQRTPD
	.long	_instrux_SQRTPS
	.long	_instrux_SQRTSD
	.long	_instrux_SQRTSS
	.long	_instrux_STC
	.long	_instrux_STD
	.long	_instrux_STI
	.long	_instrux_STMXCSR
	.long	_instrux_STOSB
	.long	_instrux_STOSD
	.long	_instrux_STOSW
	.long	_instrux_STR
	.long	_instrux_SUB
	.long	_instrux_SUBPD
	.long	_instrux_SUBPS
	.long	_instrux_SUBSD
	.long	_instrux_SUBSS
	.long	_instrux_SVDC
	.long	_instrux_SVLDT
	.long	_instrux_SVTS
	.long	_instrux_SYSCALL
	.long	_instrux_SYSENTER
	.long	_instrux_SYSEXIT
	.long	_instrux_SYSRET
	.long	_instrux_TEST
	.long	_instrux_UCOMISD
	.long	_instrux_UCOMISS
	.long	_instrux_UD0
	.long	_instrux_UD1
	.long	_instrux_UD2
	.long	_instrux_UMOV
	.long	_instrux_UNPCKHPD
	.long	_instrux_UNPCKHPS
	.long	_instrux_UNPCKLPD
	.long	_instrux_UNPCKLPS
	.long	_instrux_VERR
	.long	_instrux_VERW
	.long	_instrux_WAIT
	.long	_instrux_WBINVD
	.long	_instrux_WRMSR
	.long	_instrux_WRSHR
	.long	_instrux_XADD
	.long	_instrux_XBTS
	.long	_instrux_XCHG
	.long	_instrux_XLAT
	.long	_instrux_XLATB
	.long	_instrux_XOR
	.long	_instrux_XORPD
	.long	_instrux_XORPS
	.long	_instrux_XSTORE
	.long	_instrux_CMOVcc
	.long	_instrux_Jcc
	.long	_instrux_SETcc
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
