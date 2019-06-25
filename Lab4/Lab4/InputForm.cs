using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Lab4
{
    public class InputForm : Form
    {
        public InputForm()
        {
            Panel = new TableLayoutPanel {Dock = DockStyle.Fill};
            _textBoxes = new List<TextBox>();
            Controls.Add(Panel);
        }

        public TextBox AddTextBox(string label, string defaultText)
        {
            var subPanel = new Panel {Dock = DockStyle.Top};
            var lblLabel = new Label {Text = label, Dock = DockStyle.Top};
            var tbEdit = new TextBox {Dock = DockStyle.Fill, Text = defaultText};

            subPanel.Controls.Add(tbEdit);
            subPanel.Controls.Add(lblLabel);
            Panel.Controls.Add(subPanel);

            return tbEdit;
        }

        public TableLayoutPanel Panel { get; }

        public List<TextBox> TextBoxes => _textBoxes.ToList();

        private readonly List<TextBox> _textBoxes;

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // InputForm
            // 
            this.ClientSize = new System.Drawing.Size(367, 333);
            this.Name = "InputForm";
            this.Load += new System.EventHandler(this.InputForm_Load);
            this.ResumeLayout(false);

        }

        private void InputForm_Load(object sender, System.EventArgs e)
        {

        }
    }
}