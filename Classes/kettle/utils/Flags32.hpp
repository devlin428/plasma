//
//  Flags32.hpp
//  tests
//
//  Created by Derek Higgs on 6/10/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Flags32_hpp
#define Flags32_hpp

#include <cstdint>

namespace kettle {
namespace utils {
    /**
     * Type to hold 32 boolean flags.
     */
    typedef uint32_t flags32_t;
    
    /**
     * Class for holding 32 boolean flags.
     */
    class Flags32 {
    public:
        /**
         * Constructs with random data.
         */
        Flags32() {}
        
        /**
         * Constructs with the given flags set.
         *
         * @param flags     The initial set of flags.
         */
        explicit Flags32(flags32_t flags);
        
        /**
         * Copy constructor.
         *
         * @param flags     The flags to copy.
         */
        Flags32(const Flags32 & flags);
        
        /**
         * Deconstructor.
         */
        ~Flags32() {}
        
        /**
         * Sets a flag by the flag index.
         *
         * @param flag_index    The index of the flag.
         * @param status        The value of the flag.
         */
        Flags32 & setFlag(unsigned int flag_index, bool value);
        
        /**
         * Sets a flag to be true by the flag index.
         *
         * @param flag_index    The index of the flag.
         */
        Flags32 & setFlag(unsigned int flag_index);
        
        /**
         * Sets a flag to be false by the flag index.
         *
         * @param flag_index    The index of the flag.
         */
        Flags32 & clearFlag(unsigned int flag_index);
        
        /**
         * Sets all of the flags to false.
         */
        Flags32 & clear();
        
        /**
         * Gets the value of a flag.
         *
         * @return  Returns 0 if false.
         */
        flags32_t getFlag(unsigned int flag_index) const;
        
        /**
         * Assignment.
         *
         * @param flags     The flags to assign.
         */
        void operator=(const Flags32 & flags);
        
        /**
         * Assignment.
         *
         * @param flags     The flags to assign.
         */
        void operator=(flags32_t flags);
        
        /**
         * Converts this into an integer.
         */
        operator flags32_t() const;
        
        /**
         * Bitwise 'and' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          This instance.
         */
        Flags32 & operator&=(const Flags32 & flags);
        
        /**
         * Bitwise 'and' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          This instance.
         */
        Flags32 & operator&=(flags32_t flags);
        
        /**
         * Bitwise 'or' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          This instance.
         */
        Flags32 & operator|=(const Flags32 & flags);
        
        /**
         * Bitwise 'or' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          This instance.
         */
        Flags32 & operator|=(flags32_t flags);
        
        /**
         * Bitwise 'not' this set of flags.
         *
         * @return          This instance.
         */
        Flags32 & bitwiseNot();
        
        /**
         * Bitwise 'and' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          The result of the operation.
         */
        Flags32 operator&(const Flags32 & flags) const;
        
        /**
         * Bitwise 'and' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          The result of the operation.
         */
        Flags32 operator&(flags32_t flags) const;
        
        /**
         * Bitwise 'or' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          The result of the operation.
         */
        Flags32 operator|(const Flags32 & flags) const;
        
        /**
         * Bitwise 'or' this with another set of flags.
         *
         * @param flags     The right hand side of the operator.
         * @return          The result of the operation.
         */
        Flags32 operator|(flags32_t flags) const;
        
        /**
         * Bitwise 'not' this.
         *
         * @return          The result of the operation.
         */
        Flags32 operator~() const;
        
    protected:
        flags32_t m_flags;
    }; // class Flags32
    
    Flags32 operator&(flags32_t left_hand_side, const Flags32 & right_hand_side);
    
    Flags32 operator|(flags32_t left_hand_side, const Flags32 & right_hand_side);
} // namespace utils
} // namespace kettle

#endif /* Flags32_hpp */
