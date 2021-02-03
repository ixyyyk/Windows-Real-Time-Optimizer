using System;
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;
using System.Text;
using IniParser;
using IniParser.Model;

namespace OptimizerGUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            if (!ReloadConfig()) MessageBox.Show("Error reading config.ini. Possibly file missing?");
        }

        private void checkBoxDisableDesktop_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxDisableDesktop.Checked)
            {
                var result = richTextBoxStop.Lines.Prepend("dwm.exe");
                var result2 = result.Prepend("explorer.exe");
                richTextBoxStop.Lines = result2.ToArray();
            }
            else
            {
                String[] except = { "dwm.exe", "explorer.exe" };
                var result = richTextBoxStop.Lines.Except(except);
                richTextBoxStop.Lines = result.ToArray();
            }
        }

        private void buttonViewConfig_Click(object sender, EventArgs e)
        {
            Process.Start("notepad.exe", "config.ini");
        }

        private void buttonApply_Click(object sender, EventArgs e)
        {
            var process = new Process();
            process.StartInfo = new ProcessStartInfo("OptimizerCLI.exe")
            {
                UseShellExecute = true,
                Verb = "runas",
                Arguments = "a"
            };
            try
            {
                process.Start();
            }
            catch
            {
                MessageBox.Show("Optimizer requires administrative privileges.");
                return;
            }
            process.WaitForExit();
            MessageBox.Show("Optimization completed.");
        }

        private void buttonModifyServices_Click(object sender, EventArgs e)
        {
            Process.Start("notepad.exe", "services.txt");
        }

        private void buttonSaveConfig_Click(object sender, EventArgs e)
        {
            SaveConfig();
            MessageBox.Show("Config.ini saved.");
        }

        private void buttonReloadConfig_Click(object sender, EventArgs e)
        {
            if (ReloadConfig()) MessageBox.Show("Config reloaded.");
            else MessageBox.Show("Cannot reload config.ini, possibly file missing?");
        }
        public bool ReloadConfig()
        {
            var parser = new FileIniDataParser();
            IniData data;
            try
            {
                data = parser.ReadFile("config.ini");
            }
            catch (Exception)
            {
                   return false;
            }
            

            string strDISABLE_ALL_INTERNET = data["SERVICES"]["DISABLE_ALL_INTERNET"];
            string strDISABLE_WIRELESS_INTERNET = data["SERVICES"]["DISABLE_WIRELESS_INTERNET"];
            string strDISABLE_BLUETOOTH = data["SERVICES"]["DISABLE_BLUETOOTH"];
            string strDISABLE_AUDIO = data["SERVICES"]["DISABLE_AUDIO"];
            string strUSING_NOTEBOOK = data["SERVICES"]["USING_NOTEBOOK"];

            string strTURN_OFF_WINDOWS_DEFENDER = data["OS"]["TURN_OFF_WINDOWS_DEFENDER"];
            string strTURN_OFF_WINDOWS_FIREWALL = data["OS"]["TURN_OFF_WINDOWS_FIREWALL"];
            string strUNINSTALL_DEFAULT_WINDOWS_APPS = data["OS"]["UNINSTALL_DEFAULT_WINDOWS_APPS"];
            string strRUN_OS_TWEAKS = data["OS"]["RUN_OS_TWEAKS"];

            string strNO_PERMANENT_CHANGES = data["SETTINGS"]["NO_PERMANENT_CHANGES"];
            string strCREATE_SERVICES_RESTORE_FILE = data["SETTINGS"]["CREATE_SERVICES_RESTORE_FILE"];
            string strAUTO_APPLY_CONFIG = data["SETTINGS"]["AUTO_APPLY_CONFIG"];
            string strAUTO_START_GUI = data["SETTINGS"]["AUTO_START_GUI"];
            string strQUIET_OUTPUT = data["SETTINGS"]["QUIET_OUTPUT"];
            string strEXIT_AFTER_APPLYING = data["SETTINGS"]["EXIT_AFTER_APPLYING"];

            string strDISABLE_DESKTOP_ENVIRONMENT = data["PROCESSES"]["DISABLE_DESKTOP_ENVIRONMENT"];
            string strLOWER_NON_CRITICAL_PROCESSES = data["PROCESSES"]["LOWER_NON_CRITICAL_PROCESSES"];

            bool bDISABLE_ALL_INTERNET = bool.Parse(strDISABLE_ALL_INTERNET);
            bool bDISABLE_WIRELESS_INTERNET = bool.Parse(strDISABLE_WIRELESS_INTERNET);
            bool bDISABLE_BLUETOOTH = bool.Parse(strDISABLE_BLUETOOTH);
            bool bDISABLE_AUDIO = bool.Parse(strDISABLE_AUDIO);
            bool bUSING_NOTEBOOK = bool.Parse(strUSING_NOTEBOOK);

            bool bTURN_OFF_WINDOWS_DEFENDER = bool.Parse(strTURN_OFF_WINDOWS_DEFENDER);
            bool bTURN_OFF_WINDOWS_FIREWALL = bool.Parse(strTURN_OFF_WINDOWS_FIREWALL);
            bool bUNINSTALL_DEFAULT_WINDOWS_APPS = bool.Parse(strUNINSTALL_DEFAULT_WINDOWS_APPS);
            bool bRUN_OS_TWEAKS = bool.Parse(strRUN_OS_TWEAKS);

            bool bNO_PERMANENT_CHANGES = bool.Parse(strNO_PERMANENT_CHANGES);
            bool bCREATE_SERVICES_RESTORE_FILE = bool.Parse(strCREATE_SERVICES_RESTORE_FILE);
            bool bAUTO_APPLY_CONFIG = bool.Parse(strAUTO_APPLY_CONFIG);
            bool bAUTO_START_GUI = bool.Parse(strAUTO_START_GUI);
            bool bQUIET_OUTPUT = bool.Parse(strQUIET_OUTPUT);
            bool bEXIT_AFTER_APPLYING = bool.Parse(strEXIT_AFTER_APPLYING);

            bool bDISABLE_DESKTOP_ENVIRONMENT = bool.Parse(strDISABLE_DESKTOP_ENVIRONMENT);
            bool bLOWER_NON_CRITICAL_PROCESSES = bool.Parse(strLOWER_NON_CRITICAL_PROCESSES);

            checkedListBoxServices.SetItemChecked(0, bDISABLE_ALL_INTERNET);
            checkedListBoxServices.SetItemChecked(1, bDISABLE_WIRELESS_INTERNET);
            checkedListBoxServices.SetItemChecked(2, bDISABLE_BLUETOOTH);
            checkedListBoxServices.SetItemChecked(3, bDISABLE_AUDIO);
            checkedListBoxServices.SetItemChecked(4, bUSING_NOTEBOOK);

            checkedListBoxOS.SetItemChecked(0, bRUN_OS_TWEAKS);
            checkedListBoxOS.SetItemChecked(1, bTURN_OFF_WINDOWS_DEFENDER);
            checkedListBoxOS.SetItemChecked(2, bTURN_OFF_WINDOWS_FIREWALL);
            checkedListBoxOS.SetItemChecked(3, bUNINSTALL_DEFAULT_WINDOWS_APPS);

            checkedListBoxOptimizer.SetItemChecked(0, bNO_PERMANENT_CHANGES);
            checkedListBoxOptimizer.SetItemChecked(1, bCREATE_SERVICES_RESTORE_FILE);
            checkedListBoxOptimizer.SetItemChecked(2, bAUTO_APPLY_CONFIG);
            checkedListBoxOptimizer.SetItemChecked(3, bAUTO_START_GUI);
            checkedListBoxOptimizer.SetItemChecked(4, bQUIET_OUTPUT);
            checkedListBoxOptimizer.SetItemChecked(5, bEXIT_AFTER_APPLYING);

            checkBoxDisableDesktop.Checked = bDISABLE_DESKTOP_ENVIRONMENT;
            checkBoxLowerProcesses.Checked = bLOWER_NON_CRITICAL_PROCESSES;

            string stopList = "";
            string freezeList = "";
            string lowerList = "";
            KeyDataCollection collection = data["PROCESSES_LIST"];
            foreach (KeyData key in collection)
            {
                switch (key.Value)
                {
                    case "STOP":
                        stopList += (key.KeyName) += "\n";
                        break;
                    case "FREEZE":
                        freezeList += (key.KeyName) += "\n";
                        break;
                    case "LOWER":
                        lowerList += (key.KeyName) += "\n";
                        break;
                }
            }    
            richTextBoxStop.Text = stopList;
            richTextBoxFreeze.Text = freezeList;
            richTextBoxLowerPriority.Text = lowerList;

            richTextBoxAutorun.Clear();
            string autoRun = "";
            KeyDataCollection collection2 = data["AUTORUN"];
            foreach (KeyData key in collection2)
            {
                autoRun += key.KeyName + " = " + key.Value + "\n";
            }
            richTextBoxAutorun.Text = autoRun;
            return true;
}

        public void SaveConfig()
        {
            var parser = new FileIniDataParser();
            IniData data = parser.ReadFile("config.ini");

            data["SERVICES"]["DISABLE_ALL_INTERNET"] = checkedListBoxServices.GetItemChecked(0).ToString().ToLower();
            data["SERVICES"]["DISABLE_WIRELESS_INTERNET"] = checkedListBoxServices.GetItemChecked(1).ToString().ToLower();
            data["SERVICES"]["DISABLE_BLUETOOTH"] = checkedListBoxServices.GetItemChecked(2).ToString().ToLower();
            data["SERVICES"]["DISABLE_AUDIO"] = checkedListBoxServices.GetItemChecked(3).ToString().ToLower();
            data["SERVICES"]["USING_NOTEBOOK"] = checkedListBoxServices.GetItemChecked(4).ToString().ToLower();

            data["OS"]["RUN_OS_TWEAKS"] = checkedListBoxOS.GetItemChecked(0).ToString().ToLower();
            data["OS"]["TURN_OFF_WINDOWS_DEFENDER"] = checkedListBoxOS.GetItemChecked(1).ToString().ToLower();
            data["OS"]["TURN_OFF_WINDOWS_FIREWALL"] = checkedListBoxOS.GetItemChecked(2).ToString().ToLower();
            data["OS"]["UNINSTALL_DEFAULT_WINDOWS_APPS"] = checkedListBoxOS.GetItemChecked(3).ToString().ToLower();

            data["SETTINGS"]["NO_PERMANENT_CHANGES"] = checkedListBoxOptimizer.GetItemChecked(0).ToString().ToLower();
            data["SETTINGS"]["CREATE_SERVICES_RESTORE_FILE"] = checkedListBoxOptimizer.GetItemChecked(1).ToString().ToLower();
            data["SETTINGS"]["AUTO_APPLY_CONFIG"] = checkedListBoxOptimizer.GetItemChecked(2).ToString().ToLower();
            data["SETTINGS"]["AUTO_START_GUI"] = checkedListBoxOptimizer.GetItemChecked(3).ToString().ToLower();
            data["SETTINGS"]["QUIET_OUTPUT"] = checkedListBoxOptimizer.GetItemChecked(4).ToString().ToLower();
            data["SETTINGS"]["EXIT_AFTER_APPLYING"] = checkedListBoxOptimizer.GetItemChecked(5).ToString().ToLower();

            data["PROCESSES"]["DISABLE_DESKTOP_ENVIRONMENT"] = checkBoxDisableDesktop.Checked.ToString().ToLower();
            data["PROCESSES"]["LOWER_NON_CRITICAL_PROCESSES"] = checkBoxLowerProcesses.Checked.ToString().ToLower();

            data.Sections.RemoveSection("PROCESSES_LIST");
            data.Sections.AddSection("PROCESSES_LIST");

            foreach (string line in richTextBoxStop.Lines)
            {
                if (line.Length > 0) data["PROCESSES_LIST"].AddKey(line, "STOP");
            }

            foreach (string line in richTextBoxFreeze.Lines)
            {
                if (line.Length > 0) data["PROCESSES_LIST"].AddKey(line, "FREEZE");
            }

            foreach (string line in richTextBoxLowerPriority.Lines)
            {
                if (line.Length > 0) data["PROCESSES_LIST"].AddKey(line, "LOWER");
            }

            data.Sections.RemoveSection("AUTORUN");
            data.Sections.AddSection("AUTORUN");
            foreach (string line in richTextBoxAutorun.Lines)
            {
                if (line.Length < 2) continue; 
                if (line.IndexOf(" = ") < 1)
                {
                    MessageBox.Show("Error while parsing autorun executable. Skipping current line.");
                    continue;
                }
                
                string key = line.Substring(0, line.IndexOf(" = "));
                string value = "NORMAL";
                try
                {
                    value = line.Substring(line.IndexOf(" = ") + 3);
                }
                catch (ArgumentOutOfRangeException)
                {
                    MessageBox.Show("Error while parsing autorun executable priorty. Using NORMAL as fallback.");
                }
                
                data["AUTORUN"].AddKey(key, value);
            }
            
            parser.WriteFile("config.ini", data, new UTF8Encoding(false));
        }

        private void buttonAddAutorun_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string priority = " = NORMAL\n";
                if (radioButtonAbove.Checked) priority = " = ABOVE_NORMAL\n";
                else if (radioButtonBelow.Checked) priority = " = BELOW_NORMAL\n";
                else if (radioButtonHigh.Checked) priority = " = HIGH\n";
                string add = openFileDialog1.FileName + priority;
                richTextBoxAutorun.Text += add;
            }
        }

        private void buttonCreateRestorePoint_Click(object sender, EventArgs e)
        {
            var process = new Process();
            process.StartInfo = new ProcessStartInfo("cmd.exe")
            {
                UseShellExecute = true,
                Verb = "runas",
                Arguments = "/C \"Wmic.exe /Namespace:\\\\root\\default Path SystemRestore Call CreateRestorePoint \"WRTO Restore point\", 100, 7\""
            };
            try
            {
                process.Start();
            }
            catch
            {
                MessageBox.Show("Creating a restore point requires administrative privileges.");
                return;
            }
            process.WaitForExit();
            MessageBox.Show("Restore point created.");
        }

        private void buttonModifyPowershell_Click(object sender, EventArgs e)
        {
            Process.Start("notepad.exe", "scripts.ps1");
        }       

        private void checkedListBoxOS_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!checkedListBoxOS.GetItemChecked(0))
            {
                checkedListBoxOS.SetItemChecked(1, false);
                checkedListBoxOS.SetItemChecked(2, false);
                checkedListBoxOS.SetItemChecked(3, false);
            }
        }

        private void buttonResume_Click(object sender, EventArgs e)
        {
            var process = new Process();
            process.StartInfo = new ProcessStartInfo("OptimizerCLI.exe")
            {
                UseShellExecute = true,
                Verb = "runas",
                Arguments = "r"
            };
            try
            {
                process.Start();
            }
            catch
            {
                MessageBox.Show("Resuming requires administrative privileges.");
                return;
            }
            process.WaitForExit();
            MessageBox.Show("Resuming completed.");
        }

        private void buttonRestore_Click(object sender, EventArgs e)
        {
            var process = new Process();
            process.StartInfo = new ProcessStartInfo("OptimizerCLI.exe")
            {
                UseShellExecute = true,
                Verb = "runas",
                Arguments = "R"
            };
            try
            {
                process.Start();
            }
            catch
            {
                MessageBox.Show("Restoring requires administrative privileges.");
                return;
            }
            process.WaitForExit();
            MessageBox.Show("Restoring completed.");
        }

        private void checkBoxLowerProcesses_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxLowerProcesses.Checked)
            {
                var result = richTextBoxLowerPriority.Lines.Prepend("winlogon.exe");
                var result2 = result.Prepend("wininit.exe");
                richTextBoxLowerPriority.Lines = result2.ToArray();
            }
            else
            {
                String[] except = { "winlogon.exe", "wininit.exe" };
                var result = richTextBoxLowerPriority.Lines.Except(except);
                richTextBoxLowerPriority.Lines = result.ToArray();
            }
        }
    }
}
