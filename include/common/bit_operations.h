/**
 * @file bit_operations.h
 * @author Iván Santiago (https://github.com/ivanstgo)
 * @date 31/08/2025 - 14:15
 * @brief This header file provides macros that can be used to perform bit
 * manipulation operations.
 */

#ifndef __BIT_OPERATIONS_H
#define __BIT_OPERATIONS_H

/**
 * @brief Turns one single bit on.
 */
#define SET_BIT(B) (1u << (B))

/**
 * @brief Turns one single bit off.
 */
#define CLEAR_BIT(B) (~(1u << (B)))

#endif /* !__BIT_OPERATIONS_H */
