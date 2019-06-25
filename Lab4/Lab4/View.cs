using System.Windows.Forms;

namespace Lab4
{
    public partial class View : InputForm
    {
        private const string INPUT_FILE = "Input file name: ";
        private const string OUTPUT_FILE = "Output file name: ";
        private const string INPUT_FILE_NAME = "accept_currencies";
        private const string OUTPUT_FILE_NAME = "data_currencies";
        private const string ITERATION_COUNT = "Iteration сount: ";
        private const int DEFOULT_ITER_AMOUNT = 15;

        private readonly ViewController _viewController = new ViewController();
        
        public View()
        {
            InitializeComponent();
            CreateInputs();
            CreateButton();
        }
        
        private void CreateInputs()
        {
            Store.InputFileName = INPUT_FILE_NAME;
            Store.OutputFileName = OUTPUT_FILE_NAME;
            Store.CountIteration = DEFOULT_ITER_AMOUNT;

            var inputFileNameBox = AddTextBox(INPUT_FILE, Store.InputFileName);
            inputFileNameBox.KeyUp += _viewController.OnInputFileName;

            var outputFileNameBox = AddTextBox(OUTPUT_FILE, Store.OutputFileName);
            outputFileNameBox.KeyUp += _viewController.OnOutputFileName;

            var countIterationBox = AddTextBox(ITERATION_COUNT, Store.CountIteration.ToString());
            countIterationBox.KeyUp += _viewController.OnChangeCountIteration;
        }

        private void CreateButton()
        {
            var commitButton = new Button {Text = @"Get result"};
            commitButton.MouseClick += _viewController.CommitButtonMouseClick;
            StartPosition = FormStartPosition.CenterScreen;
            Panel.Controls.Add(commitButton);
        }

        private void View_Load(object sender, System.EventArgs e)
        {

        }
    }
}