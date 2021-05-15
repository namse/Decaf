using System;
using System.Text;
using System.Threading.Tasks;
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;

namespace parser
{
    class Program
    {
        static void Main(string[] args)
        {
            var input = System.IO.File.ReadAllText("./examples/example.dc");
            var stream = CharStreams.fromString(input);
            var lexer = new DecafLexer(stream);

            var tokens = new CommonTokenStream(lexer);
            tokens.Fill();
            foreach (var token in tokens.GetTokens())
            {
                var typeName = DecafLexer.DefaultVocabulary.GetDisplayName(token.Type);
                System.Console.WriteLine($"{token} type: {typeName}");
            }

            var parser = new DecafParser(tokens);
            parser.BuildParseTree = true;

            parser.AddParseListener(new FunctionLockCheckLisnter());

            IParseTree tree = parser.sourceFile();
        }
    }
}
