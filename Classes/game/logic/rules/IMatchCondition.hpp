//
//  IMatchCondition.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IMatchCondition_hpp
#define IMatchCondition_hpp

namespace game {
    struct MatchContext;
    
    /**
     * Interface for a match condition.
     * This class is to allow building complex conditions at runtime.
     */
    class IMatchCondition {
    public:
        /**
         * Deconstructor
         */
        virtual ~IMatchCondition() {}
        
        /**
         * Checks to see if a condition is met.
         *
         * @param context   The match context to evaluate
         */
        virtual bool isMet(const MatchContext * context) const = 0;
        
    protected:
        /**
         * Constructor
         */
        IMatchCondition() {}
        
    private:
        // disable copy and assign
        IMatchCondition(const IMatchCondition &);
        void operator=(const IMatchCondition &);
    }; // class IMatchCondition
} // namespace game

#endif /* IMatchCondition_hpp */
