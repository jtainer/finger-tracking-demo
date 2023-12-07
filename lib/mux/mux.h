// 
// Driver for I2C multiplexer
//
// Copyright (c) 2023 Jonathan Tainer
//

#ifndef I2C_MUX_H
#define I2C_MUX_H

int I2C_MUX_Init(void);

int I2C_MUX_Select(int ch);

#endif
