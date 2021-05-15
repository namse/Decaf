grammar Decaf;

@parser::members {
  
    /**
     * Returns {@code true} iff on the current index of the parser's
     * token stream a token of the given {@code type} exists on the
     * {@code HIDDEN} channel.
     *
     * @param type
     *         the type of the token on the {@code HIDDEN} channel
     *         to check.
     *
     * @return {@code true} iff on the current index of the parser's
     * token stream a token of the given {@code type} exists on the
     * {@code HIDDEN} channel.
     */
    private bool here(int type) {
        // Get the token ahead of the current index.
        int possibleIndexEosToken = this.CurrentToken.TokenIndex - 1;
        var ahead = TokenStream.Get(possibleIndexEosToken);
        // Check if the token resides on the HIDDEN channel and if it's of the
        // provided type.
        return (ahead.Channel == Lexer.Hidden) && (ahead.Type == type);
    }
}

SPACE: [ \t]+ -> skip ;

/// keywords
Function: 'function';
Var: 'var';
For: 'for';
Do: 'do';
While: 'while';
In: 'in';
/// end::keywords

sourceFile
  : functionDeclaration*
  ;

functionDeclaration
  : Function functionName '(' functionParameterList? ')' ':' functionReturnType functionBody
  ;

functionName
  : PascalCaseIdentifier
  ;

functionBody
  : block
  ;

statements
  : statement*
  ;

statement
  : iterationStatement
  | assignmentStatement
  | emptyStatement
  | variableDeclarationStatement
  | expressionStatement
  ;

block
  : '{' statements '}'
  ;

iterationStatement
  : Do block While '(' expression ')' SemiColon                                                    # DoWhileStatement
  | While '(' expression ')' block                                                        # WhileStatement
  | For '(' forStatementInit forStatementCondition forStatementUpdate ')' block           # ForStatement
  | For '(' Var CamelCaseIdentifier In expression ')' block                               # ForInStatement
  ;

forStatementInit
  : emptyStatement
  | variableDeclarationStatement
  | assignmentStatement
  | functionCallStatement
  ;

forStatementCondition
  : expression SemiColon
  ;

forStatementUpdate
  : expression
  ;

emptyStatement
  : SemiColon
  ;

assignmentStatement
  : CamelCaseIdentifier '=' expression SemiColon
  ;

variableDeclarationStatement
  : Var CamelCaseIdentifier '=' expression SemiColon
  ;

functionArgumentList
  : expression (',' expression)*
  ;

expression
  : 
    // expression '[' expressionSequence ']'                            # MemberIndexExpression
  expression '.' CamelCaseIdentifier                                    # MemberDotExpression
  // | expression arguments                                             # ArgumentsExpression
  // | New expression arguments?                                        # NewExpression
  | expression {!here(LineTerminator)}? '++'                         # PostIncrementExpression
  | expression {!here(LineTerminator)}? '--'                         # PostDecreaseExpression
  // | Delete expression                                                # DeleteExpression
  // | Void expression                                                  # VoidExpression
  // | Typeof expression                                                # TypeofExpression
  | '++' expression                                                  # PreIncrementExpression
  | '--' expression                                                  # PreDecreaseExpression
  | '+' expression                                                   # UnaryPlusExpression
  | '-' expression                                                   # UnaryMinusExpression
  | '~' expression                                                   # BitNotExpression
  | '!' expression                                                   # NotExpression
  | expression ( '*' | '/' | '%' ) expression                  # MultiplicativeExpression
  | expression ( '+' | '-' ) expression                        # AdditiveExpression
  | expression ( '<<' | '>>' | '>>>' ) expression              # BitShiftExpression
  | expression ( '<' | '>' | '<=' | '>=' ) expression          # RelationalExpression
  // | expression Instanceof expression                           # InstanceofExpression
  // | expression In expression                                   # InExpression
  | expression ( '==' | '!=' ) expression      # EqualityExpression
  | expression '&' expression                                  # BitAndExpression
  | expression '^' expression                                  # BitXOrExpression
  | expression '|' expression                                  # BitOrExpression
  | expression '&&' expression                                 # LogicalAndExpression
  | expression '||' expression                                 # LogicalOrExpression
  | expression '?' expression ':' expression             # TernaryExpression
  | expression '=' expression                                # AssignmentExpression
  | expression assignmentOperator expression                 # AssignmentOperatorExpression
  // | This                                                                   # ThisExpression
  | CamelCaseIdentifier                                                             # IdentifierExpression
  | StringLiteral                                                                # LiteralExpression
  | NumberValue # NumberExpression
  // | arrayLiteral                                                           # ArrayLiteralExpression
  // | objectLiteral                                                          # ObjectLiteralExpression
  | '(' expression ')'                                             # ParenthesizedExpression
  | functionName '(' functionArgumentList? ')' #FunctionCallExpression
  ;

expressionStatement
  : expression SemiColon
  ;

functionCallStatement
  : functionName '(' functionArgumentList? ')' SemiColon
  ;

assignmentOperator
  : '*=' 
  | '/=' 
  | '%=' 
  | '+=' 
  | '-=' 
  | '<<=' 
  | '>>=' 
  | '>>>=' 
  | '&=' 
  | '^=' 
  | '|='
  ;

value
  : expression
  ;

StringLiteral
  : '"' DoubleStringCharacter* '"'
  ;

fragment DoubleStringCharacter
  : ~["\\\r\n]
  | '\\' EscapeSequence
  | LineContinuation
  ;

fragment EscapeSequence
  : CharacterEscapeSequence
  | '0'
  | HexEscapeSequence
  | UnicodeEscapeSequence
  ;
fragment CharacterEscapeSequence
  : SingleEscapeCharacter
  | NonEscapeCharacter
  ;
fragment HexEscapeSequence
  : 'x' HexDigit HexDigit
  ;
fragment UnicodeEscapeSequence
  : 'u' HexDigit HexDigit HexDigit HexDigit
  ;
fragment SingleEscapeCharacter
  : ['"\\bfnrtv]
  ;

fragment NonEscapeCharacter
  : ~['"\\bfnrtv0-9xu\r\n]
  ;

fragment EscapeCharacter
  : SingleEscapeCharacter
  | DecimalDigit
  | [xu]
  ;
fragment LineContinuation
  : '\\' LineTerminatorSequence 
  ;
fragment LineTerminatorSequence
  : '\r\n'
  | LineTerminator
  ;

LineTerminator
  : [\r\n\u2028\u2029] -> channel(HIDDEN)
  ;

functionReturnType
  : typeIdentifier
  ;

functionParameterList
  : typeIdentifier variableIdentifier ( ',' typeIdentifier variableIdentifier )*
  ;

typeIdentifier
  : PascalCaseIdentifier
  ;

variableIdentifier
  : CamelCaseIdentifier
  ;

fragment Alphabet
  : LowerCaseAlphabet
  | UpperCaseAlphabet
  ;

NumberValue
  : DecimalDigit+
  ;

fragment DecimalDigit
  : [0-9]
  ;
 
fragment UpperCaseAlphabet: 'A'..'Z';

fragment LowerCaseAlphabet: 'a'..'z';

fragment HexDigit
  : [0-9a-fA-F]
  ;
fragment AlphaNumeric
  : Alphabet
  | DecimalDigit
  ;

CamelCaseIdentifier
  : LowerCaseAlphabet AlphaNumeric*
  ;

PascalCaseIdentifier
  : UpperCaseAlphabet AlphaNumeric*
  ;

SemiColon : ';';