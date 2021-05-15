using Antlr4.Runtime;
using Antlr4.Runtime.Misc;
using System.Linq;

namespace parser
{
    public class FunctionLockCheckLisnter: DecafBaseListener
    {
        public override void ExitEveryRule([NotNull] ParserRuleContext context)
        {
            var last = context.children?.Last();
            if (last is null || last.GetType() == typeof(Antlr4.Runtime.Tree.TerminalNodeImpl)) {
                return;
            }

            System.Console.WriteLine($"[DEBUG] type: {last.GetType()} text: {last.GetText()}");
        }
    }
}
