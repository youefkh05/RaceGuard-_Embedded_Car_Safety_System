/*
 * BIT_MATH.h
 *
 * Created: 9/15/2023 10:40:17 AM
 *  Author: oraga
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*-----------------------------BIT MATH OPERATION-----------------------------*/
#define SET_BIT(REG,BIT) REG|=(1<<BIT)
#define CLR_BIT(REG,BIT) REG&=~(1<<BIT)
#define TGL_BIT(REG,BIT) REG^=(1<<BIT)
#define GET_BIT(REG,BIT) ((REG>>BIT)&0x01)



#endif /* BIT_MATH_H_ */