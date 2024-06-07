void MakeJetHistos(const char* filename) {
    // RDataFrame from file
    ROOT::RDataFrame df("Events", filename);

    // Columns to be plotted
    std::vector<std::string> jetCols = {
        "Jet_pt",
        "Jet_eta",
        "Jet_phi",
        "Jet_mass"
    };

    // 2D array to hold the ranges for each histogram
    int histranges[4][2] = {
        {0, 100},
        {0, 100},
        {0, 100},
        {0, 100},
    };

    for (int i = 0; i < jetCols.size(); ++i) {
        const auto& jetCol = jetCols[i];

        std::string histName = jetCol + "_Hist";
        std::string histTitle = jetCol + " Distribution;" + jetCol + ";Events";

        // Create histogram
        auto hist = df.Histo1D({histName.c_str(), histTitle.c_str(), 100, static_cast<double>(histranges[i][0]), static_cast<double>(histranges[i][1])}, jetCol);

        // Create canvas
        auto canvas = new TCanvas("canvas", (jetCol + " Histogram").c_str(), 800, 600);

        // Draw and save histogram
        hist->Draw();
        canvas->SaveAs((jetCol + "histo.png").c_str());

        // Clean up
        delete canvas;
    }
}