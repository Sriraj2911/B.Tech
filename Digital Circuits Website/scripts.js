// Function to generate random values from [0, 1, X]
function randomValue() {
    const values = ['0', '1', 'X'];
    const idx = Math.floor(Math.random() * values.length);
  return values[idx];
}

// Function to cycle value on click between "0" -> "1" -> "X" -> "0" ...
function cycleValue(cell) {
    const values = ['0', '1', 'X'];
    let currentIndex = values.indexOf(cell.innerText);
    let nextIndex = (currentIndex + 1) % values.length;
    cell.innerText = values[nextIndex];
}

// Function to generate the random truth table, with desired number of input bits
function generateTruthTable() {
    const input = document.getElementById('inputBits');
    const n = parseInt(input.value, 10);
    const min = parseInt(input.min, 10);
    const max = parseInt(input.max, 10);

    // To prevent the entry of numbers outside the range
    if (n < min || n > max || isNaN(n)) {
        alert(`Please enter a number between ${min} and ${max}.`);
        input.value = min; // or you can reset to last valid value
        return;
    }
        const rows = Math.pow(2, n);
        let table = '<table><thead><tr>';

        // Table header
        let A = 65;
        let char;
        for (let i = 0; i < n; i++) {
            char = String.fromCharCode(A+i)
            table += `<th>x${i+1}</th>`;
        }
        table += `<th>x${n+1}</th>`
        table += '</tr></thead><tbody>';

        // Table rows
        for (let i = 0; i < rows; i++) {
            let binaryStr = i.toString(2).padStart(n, '0'); // get n-bit binary string
            table += '<tr>';
            for (let bit of binaryStr) {
                table += `<td>${bit}</td>`;
            }
            table += `<td class="clickable">${randomValue()}</td>`;
            table += '</tr>';
        }
        table += '</tbody></table>';

        document.getElementById('truthTableContainer').innerHTML = table;
        // Add click event listeners to last column cells
        const clickableCells = document.querySelectorAll('#truthTableContainer td.clickable');
        clickableCells.forEach(cell => {
            cell.addEventListener('click', () => {
            cycleValue(cell);
            const n = parseInt(document.getElementById("inputBits").value, 10);
            const outputs = getTruthTableOutputs();
            showKmap(n, outputs);              // update K-map to stay in sync
            updateExpressionsAndVerilog(n, outputs);
        });

        });
        document.getElementById("expressionFormat").selectedIndex = 0;
        document.getElementById("output").innerText = "";

        const outputs = getTruthTableOutputs();
        showKmap(n, outputs);   
    }

    // Generate initial table
    generateTruthTable();

// Table with all 1s
function generateOnes() {
    const input = document.getElementById('inputBits');
    const n = parseInt(input.value, 10);
    const min = parseInt(input.min, 10);
    const max = parseInt(input.max, 10);

    // To prevent the entry of numbers outside the range
    if (n < min || n > max || isNaN(n)) {
        alert(`Please enter a number between ${min} and ${max}.`);
        input.value = min; // or you can reset to last valid value
        return;
    }
    const rows = Math.pow(2, n);
    let table = '<table><thead><tr>';

    // Table header
    let A = 65;
    let char;
    for (let i = 0; i < n; i++) {
        char = String.fromCharCode(A+i)
        table += `<th>${char}</th>`;
    }
    table += `<th>${String.fromCharCode(A+n)}</th>`
    table += '</tr></thead><tbody>';

    // Table rows
    for (let i = 0; i < rows; i++) {
        let binaryStr = i.toString(2).padStart(n, '0'); // get n-bit binary string
        table += '<tr>';
        for (let bit of binaryStr) {
            table += `<td>${bit}</td>`;
        }
        table += `<td class="clickable">${1}</td>`;
        table += '</tr>';
    }
    table += '</tbody></table>';

    document.getElementById('truthTableContainer').innerHTML = table;
    // Add click event listeners to last column cells
    const clickableCells = document.querySelectorAll('#truthTableContainer td.clickable');
    clickableCells.forEach(cell => {
        cell.addEventListener('click', () => cycleValue(cell));
    });
    // Reset dropdown + clear solution
    document.getElementById("expressionFormat").selectedIndex = 0;
    document.getElementById("output").innerText = "";

    const outputs = getTruthTableOutputs();
    showKmap(n, outputs);   
    }
// Table with all 0s
function generateZeroes() {
    const input = document.getElementById('inputBits');
    const n = parseInt(input.value, 10);
    const min = parseInt(input.min, 10);
    const max = parseInt(input.max, 10);

    // To prevent the entry of numbers outside the range
    if (n < min || n > max || isNaN(n)) {
        alert(`Please enter a number between ${min} and ${max}.`);
        input.value = min; // or you can reset to last valid value
        return;
    }
    const rows = Math.pow(2, n);
    let table = '<table><thead><tr>';

    // Table header
    let A = 65;
    let char;
    for (let i = 0; i < n; i++) {
        char = String.fromCharCode(A+i)
        table += `<th>${char}</th>`;
    }
    table += `<th>${String.fromCharCode(A+n)}</th>`
    table += '</tr></thead><tbody>';

    // Table rows
    for (let i = 0; i < rows; i++) {
        let binaryStr = i.toString(2).padStart(n, '0'); // get n-bit binary string
        table += '<tr>';
        for (let bit of binaryStr) {
            table += `<td>${bit}</td>`;
        }
        table += `<td class="clickable">${0}</td>`;
        table += '</tr>';
    }
    table += '</tbody></table>';

    document.getElementById('truthTableContainer').innerHTML = table;
    // Add click event listeners to last column cells
    const clickableCells = document.querySelectorAll('#truthTableContainer td.clickable');
    clickableCells.forEach(cell => {
        cell.addEventListener('click', () => cycleValue(cell));
    });
    // Reset dropdown + clear solution
    document.getElementById("expressionFormat").selectedIndex = 0;
    document.getElementById("output").innerText = "";

    const outputs = getTruthTableOutputs();
    showKmap(n, outputs);   
    }

function getTruthTableOutputs() {
    const rows = document.querySelectorAll("#truthTableContainer tbody tr");
    let outputs = [];
    rows.forEach(row => {
        let cells = row.querySelectorAll("td");
        outputs.push(cells[cells.length - 1].innerText);
    });
    return outputs;
}

// Generate SOP and POS from truth table
// inputs: number of variables, truth table array of outputs
// truthTable: array of 0/1 values corresponding to minterms in binary order

function getSOPandPOS(numVars, truthTable) {
  let sopTerms = [];
  let posTerms = [];

  for (let i = 0; i < truthTable.length; i++) {
    let binary = i.toString(2).padStart(numVars, "0").split("");

    if (truthTable[i] === '1') { // output = 1
      let term = binary.map((bit, idx) =>
        bit === "1" ? `x${idx + 1}` : `x${idx + 1}'`
      ).join("");
      sopTerms.push(term);
    } else if (truthTable[i] === '0') { // output = 0
      let term = binary.map((bit, idx) =>
        bit === "0" ? `x${idx + 1}` : `x${idx + 1}'`
      ).join(" + ");
      posTerms.push(`(${term})`);
    }
    // skip 'X' (don't care)
  }

  let sop = sopTerms.length ? sopTerms.join(" + ") : "0";
  let pos = posTerms.length ? posTerms.join("") : "1";

  return { SOP: sop, POS: pos };
}

function getSOP() {
  const n = parseInt(document.getElementById("inputBits").value, 10);
  const outputs = getTruthTableOutputs();
  const { SOP } = getSOPandPOS(n, outputs);
  return SOP;
}

function getPOS() {
  const n = parseInt(document.getElementById("inputBits").value, 10);
  const outputs = getTruthTableOutputs();
  const { POS } = getSOPandPOS(n, outputs);
  return POS;
}

// Minimal SOP
function minimizeSOP(numVars, truthTable) {
  let minterms = [];
  for (let i = 0; i < truthTable.length; i++) {
    if (truthTable[i] === '1') minterms.push(i);
  }
  if (minterms.length === 0) return "0";
  if (minterms.length === Math.pow(2, numVars)) return "1";

  let terms = minterms.map(m => m.toString(2).padStart(numVars, "0"));

  function combine(a, b) {
    let diff = 0, res = "";
    for (let i = 0; i < a.length; i++) {
      if (a[i] !== b[i]) {
        diff++;
        res += "-";
      } else {
        res += a[i];
      }
    }
    return diff === 1 ? res : null;
  }

  let groups = [...terms];
  let changed;
  do {
    changed = false;
    let newGroups = [];
    let used = new Set();
    for (let i = 0; i < groups.length; i++) {
      for (let j = i+1; j < groups.length; j++) {
        let c = combine(groups[i], groups[j]);
        if (c) {
          newGroups.push(c);
          used.add(i); used.add(j);
          changed = true;
        }
      }
    }
    groups = [...new Set([...groups.filter((_,i)=>!used.has(i)), ...newGroups])];
  } while (changed);

  function termToExpr(term) {
    return term.split("").map((ch, idx) => {
      if (ch === "1") return `x${idx+1}`;
      if (ch === "0") return `x${idx+1}'`;
      return ""; // "-" = don't care
    }).join("");
  }

  return groups.map(termToExpr).join(" + ");
}
// Minimal POS: minimize complement with SOP, then apply De Morgan's
function minimizePOS(numVars, truthTable) {
  // Build complement truth table
  let inverted = truthTable.map(v => v === '0' ? '1' : '0');

  // Get minimal SOP of f'
  let sopOfComplement = minimizeSOP(numVars, inverted);
  if (sopOfComplement === "0") return "1"; // f' = 0 => f = 1
  if (sopOfComplement === "1") return "0"; // f' = 1 => f = 0

  // Convert each product term of f' into a sum term for f
  let terms = sopOfComplement.split(" + ").map(product => {
    let factors = product.match(/x\d+'?|/g).filter(f => f !== "");
    return "(" + factors.map(f => {
      if (f.endsWith("'")) return f.slice(0, -1); // x' => x
      return f + "'"; // x => x'
    }).join(" + ") + ")";
  });

  return terms.join("");
}
// The smaller expression among Minimal POS and Minimal SOP
function getSmallerExpression(numVars, truthTable) {
  const sop = minimizeSOP(numVars, truthTable);
  const pos = minimizePOS(numVars, truthTable);

  // size metric: number of characters (or count of literals)
  const size = expr => expr.replace(/\s+/g, "").length;

  return size(sop) <= size(pos)
    ? { type: "Minimal SOP", expr: sop }
    : { type: "Minimal POS", expr: pos };
}


// Convert a minimal SOP or POS expression string into a Verilog RHS expression
// Accepts patterns like:
//   SOP: "x1'x2 + x2x3 + x1x3"
//   POS: "(x1 + x2)(x2 + x3)(x1' + x3)"
// Returns a string like "(~x1 & x2) | (x2 & x3) | (x1 & x3)"  (SOP)
// or "(x1 | x2) & (x2 | x3) & (~x1 | x3)" (POS)
function exprToVerilog(expr) {
  if (!expr || expr.trim() === "") return "/* empty */";

  expr = expr.trim();

  // trivial constants
  if (expr === "0") return "1'b0";
  if (expr === "1") return "1'b1";

  // helper to convert a variable token like "x3" or "x2'" into verilog token "~x3" or "x2"
  function tokenToVerilog(tok) {
    tok = tok.trim();
    const m = tok.match(/^x(\d+)(')?$/);
    if (!m) throw new Error("Unexpected token: " + tok);
    const varName = `x${m[1]}`;
    const neg = !!m[2];
    return neg ? `~${varName}` : varName;
  }

  // detect POS (contains parentheses around sums) or SOP (use + and adjacency products)
  const isPOS = /\([^\)]+\)/.test(expr);

  if (isPOS) {
    // Extract groups like "(x1 + x2)" -> convert each to (a | b | ~c)
    const groups = expr.match(/\([^\)]+\)/g);
    if (!groups) throw new Error("Can't parse POS expression: " + expr);

    const verilogGroups = groups.map(g => {
      // remove parentheses and split by '+'
      const inner = g.slice(1, -1);
      const parts = inner.split(/\+/).map(s => s.trim()).filter(Boolean);
      const mapped = parts.map(tokenToVerilog);
      return "(" + mapped.join(" | ") + ")";
    });

    // POS is product (AND) of sums -> join with &
    return verilogGroups.join(" & ");
  } else {
    // SOP: split by + to get product terms.
    // Note: product terms may be written without any operator between variables, e.g. "x1'x2"
    // We'll split by '+' first, then extract variable tokens using regex.
    const products = expr.split(/\+/).map(s => s.trim()).filter(Boolean);

    const verilogProducts = products.map(prod => {
      // find all x# or x#' tokens in order
      const tokens = prod.match(/x\d+'?|x\d+/g);
      if (!tokens) throw new Error("Can't parse product term: " + prod);
      const mapped = tokens.map(tokenToVerilog);
      // single literal product -> no parentheses necessary but keep them for clarity
      return "(" + mapped.join(" & ") + ")";
    });

    // SOP is sum (OR) of products -> join with |
    return verilogProducts.join(" | ");
  }
}

// Create a full Verilog module string from expression
// numVars: number of inputs (n) => x1..xn
// expr: minimal expression string (SOP or POS) or canonical
// moduleName: optional, defaults to 'logic_module'
// outName: optional, defaults to 'F'
function generateVerilogModule(numVars, expr, moduleName = "logic_module", outName = "F") {
  // Defensive: sanity-check numVars
  if (!Number.isInteger(numVars) || numVars < 1) throw new Error("numVars must be positive integer");

  const inputs = [];
  for (let i = 1; i <= numVars; i++) inputs.push(`x${i}`);

  const headerPorts = [...inputs, outName].join(", ");
  const inputList = inputs.join(", ");

  let rhs;
  try {
    rhs = exprToVerilog(expr);
  } catch (e) {
    rhs = `/* parse error: ${e.message} */ 1'bx`;
  }

  const moduleLines = [];
  moduleLines.push(`module ${moduleName} (${headerPorts});`);
  moduleLines.push(`  input ${inputList};`);
  moduleLines.push(`  output ${outName};`);
  moduleLines.push("");
  moduleLines.push(`  // Combinational logic`);
  moduleLines.push(`  assign ${outName} = ${rhs};`);
  moduleLines.push("");
  moduleLines.push(`endmodule`);

  return moduleLines.join("\n");
}

// Generate a Verilog testbench for the given module
// numVars = number of inputs (n), moduleName = your logic module name
function generateVerilogTestbench(numVars, moduleName = "logic_gen", outName = "F") {
  const inputs = [];
  for (let i = 1; i <= numVars; i++) inputs.push(`x${i}`);

  // instance port connections
  const portMap = [...inputs.map(v => `.${v}(${v})`), `.${outName}(${outName})`].join(", ");

  const tbLines = [];
  tbLines.push(`module ${moduleName}_tb;`);
  tbLines.push(`  reg ${inputs.join(", ")};`);
  tbLines.push(`  wire ${outName};`);
  tbLines.push("");
  tbLines.push(`  // Instantiate DUT`);
  tbLines.push(`  ${moduleName} uut (${portMap});`);
  tbLines.push("");
  tbLines.push(`  integer i;`);
  tbLines.push("  initial begin");
  tbLines.push(`    $display("Testing ${moduleName}...");`);
  tbLines.push(`    $display("Inputs -> Output");`);
  tbLines.push("");
  tbLines.push(`    for (i = 0; i < ${1 << numVars}; i = i + 1) begin`);
  tbLines.push(`      {${inputs.join(", ")}} = i;`);
  tbLines.push("      #1; // small delay");
  tbLines.push(`      $display("%b -> %b", {${inputs.join(", ")}}, ${outName});`);
  tbLines.push("    end");
  tbLines.push("");
  tbLines.push("    $finish;");
  tbLines.push("  end");
  tbLines.push("endmodule");

  return tbLines.join("\n");
}

// Gray code for length bits: returns array of binary strings length `bits`
function graySequence(bits) {
  const n = 1 << bits;
  const seq = [];
  for (let i = 0; i < n; i++) {
    const g = i ^ (i >> 1);
    seq.push(g.toString(2).padStart(bits, "0"));
  }
  return seq;
}

// Build and render K-map into #kmapContainer
// numVars: number of input vars (2..5). outputs: array of '0'|'1'|'X' of length 2^numVars
// Build and render K-map into #kmapContainer
// numVars: number of input vars (2..5). outputs: array of '0'|'1'|'X' of length 2^numVars
function showKmap(numVars, outputs) {
  const container = document.getElementById("kmapContainer");
  if (!container) return;

  if (!Number.isInteger(numVars) || numVars < 2 || numVars > 5) {
    container.innerHTML = "<p>Unsupported number of variables (2..5).</p>";
    return;
  }
  if (!Array.isArray(outputs) || outputs.length !== (1 << numVars)) {
    container.innerHTML = "<p>Invalid outputs array.</p>";
    return;
  }

  const rowBits = Math.floor(numVars / 2);
  const colBits = numVars - rowBits;
  const rows = 1 << rowBits;
  const cols = 1 << colBits;

  const rowLabels = graySequence(rowBits);
  const colLabels = graySequence(colBits);

  let html = '<table class="kmap"><thead><tr>';
  html += `<th class="corner label"></th>`;

  for (let c = 0; c < cols; c++) {
    html += `<th class="label">${colLabels[c]}</th>`;
  }
  html += '</tr></thead><tbody>';

  for (let r = 0; r < rows; r++) {
    html += `<tr><th class="label">${rowLabels[r]}</th>`;
    for (let c = 0; c < cols; c++) {
      const bitstr = (rowLabels[r] + colLabels[c]).padStart(numVars, '0');
      const index = parseInt(bitstr, 2);
      const val = outputs[index] ?? 'X';

      let cls = "kcell";
      if (val === '1') cls += " one";
      else if (val === '0') cls += " zero";
      else cls += " dc";

      html += `<td class="${cls}" data-index="${index}">${val}</td>`;
    }
    html += '</tr>';
  }
  html += '</tbody></table>';
  container.innerHTML = html;

  // 🔑 Add click listeners for toggling values
  const cells = container.querySelectorAll("td.kcell");
  cells.forEach(cell => {
    cell.addEventListener("click", () => {
      const idx = parseInt(cell.dataset.index, 10);
      let val = outputs[idx];
      if (val === '0') val = '1';
      else if (val === '1') val = 'X';
      else val = '0';
      outputs[idx] = val;

      // update this cell style/text
      cell.textContent = val;
      cell.className = "kcell " + (val === '1' ? "one" : val === '0' ? "zero" : "dc");

      // 🔑 also update the truth table cell
      const truthCells = document.querySelectorAll("#truthTableContainer td.clickable");
      if (truthCells[idx]) truthCells[idx].textContent = val;

      // 🔑 re-run SOP/POS/minimal/verilog/testbench generation
      updateExpressionsAndVerilog(numVars, outputs);
    });
  });
}

function updateExpressionsAndVerilog(n, outputs) {
  const { SOP, POS } = getSOPandPOS(n, outputs);
  const smallest = getSmallerExpression(n, outputs);

  const dropdown = document.getElementById("expressionFormat");
  const output = document.getElementById("output");

  let text = "";
  if (dropdown.value === "SOP") {
    text = "Canonical SOP: " + SOP + "\n" +
           "Simplified expression: " + smallest.expr;
  } else if (dropdown.value === "POS") {
    text = "Canonical POS: " + POS + "\n" +
           "Simplified expression: " + smallest.expr;
  }
  output.innerText = text;

  if (dropdown.value === "SOP" || dropdown.value === "POS") {
    const verilog = generateVerilogModule(n, smallest.expr, "logic_gen", "F");
    document.getElementById("verilogOutput").innerText = verilog;

    const tb = generateVerilogTestbench(n, "logic_gen", "F");
    document.getElementById("testbenchOutput").innerText = tb;
  }
}

