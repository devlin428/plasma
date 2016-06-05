//
//  MatchConditionBuilder.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "MatchConditionBuilder.hpp"

#include "ReferenceCountedObject.hpp"

#include "MatchConditionFunctionPointer.hpp"
#include "MatchConditionAnd.hpp"
#include "MatchConditionOr.hpp"
#include "MatchConditionNot.hpp"

namespace game {
    /**
     * The type of conditions supported for the builder.
     */
    enum ConditionType {
        /**
         * The condition is based on a function pointer of type
         * match_condition_t.
         */
        kConditionTypeFunctionPointer,
        
        /**
         * The condition is any condition AND any condition.
         */
        kConditionTypeAnd,
        
        /**
         * The condition is any condition OR any condition.
         */
        kConditionTypeOr,
        
        /**
         * The condition is NOT any condition.
         */
        kConditionTypeNot,
        
        /**
         * There is no condition. This value means the condition has been
         * destroyed.
         */
        kConditionTypeNone
    };
    
    /**
     * A condition for the builder to construct.
     */
    class IBuilderCondition : public kettle::utils::ReferenceCountedObject {
    public:
        /**
         * Deconstructor
         */
        virtual ~IBuilderCondition() {}
        
        /**
         * Builds the condition.
         *
         * @return  The new condition based on this builder condition.
         */
        virtual IMatchCondition * createCondition() const = 0;
        
    protected:
        /**
         * Constructor
         */
        IBuilderCondition() {}
        
    private:
        // disable copy and assign
        IBuilderCondition(const IBuilderCondition &);
        void operator=(const IBuilderCondition &);
    }; // class BuilderCondition
    
    /**
     * A builder condition that takes a function pointer.
     */
    class BuilderConditionFunctionPointer : public IBuilderCondition {
    public:
        /**
         * Constructs a builder condition to check using a function pointer.
         */
        BuilderConditionFunctionPointer(match_condition_t condition) :
                m_condition(condition) {}
        
        /**
         * Deconstructor
         */
        ~BuilderConditionFunctionPointer() {}
        
        /**
         * Builds the condition.
         *
         * @return  The new condition based on this builder condition.
         */
        IMatchCondition * createCondition() const;
        
    protected:
        /**
         * The function pointer to check the condition.
         */
        match_condition_t m_condition;
        
    private:
        // disable copy and assign
        BuilderConditionFunctionPointer(const BuilderConditionFunctionPointer &);
        void operator=(const BuilderConditionFunctionPointer &);
    }; // class BuilderConditionFunctionPointer
    
    /**
     * A builder that combined two conditions as an and statement.
     */
    class BuilderConditionAnd : public IBuilderCondition {
    public:
        /**
         * Constructs the builder to make an and statement out of the two
         * conditions.
         *
         * @param left_hand_side    The left hand side of the statement.
         * @param right_hand_side   The right hand side of the statement.
         */
        BuilderConditionAnd(IBuilderCondition * left_hand_side, IBuilderCondition * right_hand_side);
        
        /**
         * Deconstructor
         */
        ~BuilderConditionAnd();
        
        /**
         * Builds the condition.
         *
         * @return  The new condition based on this builder condition.
         */
        IMatchCondition * createCondition() const;
        
    protected:
        IBuilderCondition * m_left_hand_side, * m_right_hand_side;
        
    private:
        // disable copy and assign
        BuilderConditionAnd(const BuilderConditionAnd &);
        void operator=(const BuilderConditionAnd &);
    }; // class BuilderConditionAnd
    
    /**
     * A builder that combined two conditions as or and statement.
     */
    class BuilderConditionOr : public IBuilderCondition {
    public:
        /**
         * Constructs the builder to make an or statement out of the two
         * conditions.
         *
         * @param left_hand_side    The left hand side of the statement.
         * @param right_hand_side   The right hand side of the statement.
         */
        BuilderConditionOr(IBuilderCondition * left_hand_side, IBuilderCondition * right_hand_side);
        
        /**
         * Deconstructor
         */
        ~BuilderConditionOr();
        
        /**
         * Builds the condition.
         *
         * @return  The new condition based on this builder condition.
         */
        IMatchCondition * createCondition() const;
        
    protected:
        IBuilderCondition * m_left_hand_side, * m_right_hand_side;
        
    private:
        // disable copy and assign
        BuilderConditionOr(const BuilderConditionOr &);
        void operator=(const BuilderConditionOr &);
    }; // class BuilderConditionOr
    
    /**
     * A builder condition that takes negates a condtion.
     */
    class BuilderConditionNot : public IBuilderCondition {
    public:
        /**
         * Constructs the builder to negate the condiont.
         *
         * @param condition     The condition to negate.
         */
        BuilderConditionNot(IBuilderCondition * condition);
        
        /**
         * Deconstructor
         */
        ~BuilderConditionNot();
        
        /**
         * Builds the condition.
         *
         * @return  The new condition based on this builder condition.
         */
        IMatchCondition * createCondition() const;
        
    protected:
        /**
         * The condition to negate.
         */
        IBuilderCondition * m_condition;
        
    private:
        // disable copy and assign
        BuilderConditionNot(const BuilderConditionNot &);
        void operator=(const BuilderConditionNot &);
    }; // class BuilderConditionNot
    
    // MatchConditionBuilder
    
    /**
     * The private implementation of MatchConditionBuilder.
     */
    struct MatchConditionBuilder::PrivateImplementation {
        /**
         * The condition which the builder is currently building.
         */
        IBuilderCondition * builder_condition;
        
        /**
         * Starts the builder with the condition.
         */
        PrivateImplementation(match_condition_t condition);
        
        /**
         * Destorys the implementation.
         */
        ~PrivateImplementation();
        
        /**
         * Sets the builder condition to the new condition.
         */
        void setBuilderCondition(IBuilderCondition * condition);
    }; // struct MatchConditionBuilder::PrivateImplementation
    
    MatchConditionBuilder::MatchConditionBuilder(match_condition_t condition) :
            m_private_implementation(new PrivateImplementation(condition)) {}
    
    MatchConditionBuilder::~MatchConditionBuilder() {
        if(m_private_implementation) {
            delete m_private_implementation;
            m_private_implementation = nullptr;
        }
    }
    
    const IMatchCondition * MatchConditionBuilder::createCondition() const {
        return m_private_implementation->builder_condition->createCondition();
    }
    
    MatchConditionBuilder & MatchConditionBuilder::andCondition(const MatchConditionBuilder & right_hand_side) {
        IBuilderCondition * new_condition = new BuilderConditionAnd(m_private_implementation->builder_condition,
                                                                    right_hand_side.m_private_implementation->builder_condition);
        m_private_implementation->setBuilderCondition(new_condition);
        new_condition->release();
        return *this;
    }
    
    MatchConditionBuilder & MatchConditionBuilder::orCondition(const MatchConditionBuilder & right_hand_side) {
        IBuilderCondition * new_condition = new BuilderConditionOr(m_private_implementation->builder_condition,
                                                                   right_hand_side.m_private_implementation->builder_condition);
        m_private_implementation->setBuilderCondition(new_condition);
        new_condition->release();
        return *this;
    }
    
    MatchConditionBuilder & MatchConditionBuilder::notCondition() {
        IBuilderCondition * new_condition = new BuilderConditionNot(m_private_implementation->builder_condition);
        m_private_implementation->setBuilderCondition(new_condition);
        new_condition->release();
        return *this;
    }
    
    // MatchConditionBuilder::PrivateImplementation
    
    MatchConditionBuilder::PrivateImplementation::PrivateImplementation(match_condition_t condition) :
            builder_condition(new BuilderConditionFunctionPointer(condition)) {}
    
    MatchConditionBuilder::PrivateImplementation::~PrivateImplementation() {
        if(builder_condition) {
            builder_condition->release();
            builder_condition = nullptr;
        }
    }
    
    void MatchConditionBuilder::PrivateImplementation::setBuilderCondition(IBuilderCondition * condition) {
        condition->retain();
        builder_condition->release();
        builder_condition = condition;
    }
    
    // BuilderConditionFunctionPointer
    
    IMatchCondition * BuilderConditionFunctionPointer::createCondition() const {
        return new MatchConditionFunctionPointer(m_condition);
    }
    
    // BuilderConditionAnd
    
    BuilderConditionAnd::BuilderConditionAnd(IBuilderCondition * left_hand_side, IBuilderCondition * right_hand_side) :
            m_left_hand_side(left_hand_side),
            m_right_hand_side(right_hand_side) {
        m_left_hand_side->retain();
        m_right_hand_side->retain();
    }
    
    BuilderConditionAnd::~BuilderConditionAnd() {
        if(m_left_hand_side) {
            m_left_hand_side->release();
            m_left_hand_side = nullptr;
        }
        if(m_right_hand_side) {
            m_right_hand_side->release();
            m_right_hand_side = nullptr;
        }
    }
    
    IMatchCondition * BuilderConditionAnd::createCondition() const {
        return new MatchConditionAnd(m_left_hand_side->createCondition(),
                                     m_right_hand_side->createCondition());
    }
    
    // BuilderConditionOr
    
    BuilderConditionOr::BuilderConditionOr(IBuilderCondition * left_hand_side, IBuilderCondition * right_hand_side) :
            m_left_hand_side(left_hand_side),
            m_right_hand_side(right_hand_side) {
        m_left_hand_side->retain();
        m_right_hand_side->retain();
    }
    
    BuilderConditionOr::~BuilderConditionOr() {
        if(m_left_hand_side) {
            m_left_hand_side->release();
            m_left_hand_side = nullptr;
        }
        if(m_right_hand_side) {
            m_right_hand_side->release();
            m_right_hand_side = nullptr;
        }
    }
    
    IMatchCondition * BuilderConditionOr::createCondition() const {
        return new MatchConditionOr(m_left_hand_side->createCondition(),
                                    m_right_hand_side->createCondition());
    }
    
    // BuilderConditionNot
    
    BuilderConditionNot::BuilderConditionNot(IBuilderCondition * condition) :
            m_condition(condition) {
        m_condition->retain();
    }
    
    BuilderConditionNot::~BuilderConditionNot() {
        if(m_condition) {
            m_condition->release();
            m_condition = nullptr;
        }
    }
    
    IMatchCondition * BuilderConditionNot::createCondition() const {
        return new MatchConditionNot(m_condition->createCondition());
    }
} // namespace game
