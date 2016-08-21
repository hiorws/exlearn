defmodule ExLearn.NeuralNetwork.Worker.PredictTest do
  use ExUnit.Case, async: true

  alias ExLearn.{Matrix, TestUtils}
  alias ExLearn.NeuralNetwork.{Worker, WorkerFixtures}

  setup do
    name    = {:global, make_ref()}
    options = [name: name]

    {:ok, setup: %{
      name:    name,
      options: options
    }}
  end

  test "#predict with data in file returns the prediction", %{setup: setup} do
    %{name: worker, options: options} = setup

    input         = Matrix.new(1, 3, [[1, 2, 3]])
    output        = Matrix.new(1, 2, [[1897, 2784]])
    data          = [input]
    expected      = [%{input: input, output: output}]
    network_state = WorkerFixtures.initial_network_state
    path          = TestUtils.temp_file_path()

    TestUtils.write_to_file_as_binary(data, path)

    args = %{data: %{location: :file, source: [path]}}

    {:ok, _pid} = Worker.start_link(args, options)

    :ok    = Worker.predict(network_state, worker)
    result = Worker.get(worker)

    assert result == expected

    :ok = File.rm(path)
  end

  test "#predict with data in memory returns the prediction", %{setup: setup} do
    %{
      name:    worker,
      options: options
    } = setup

    input         = Matrix.new(1, 3, [[1, 2, 3]])
    output        = Matrix.new(1, 2, [[1897, 2784]])
    data          = [input]
    expected      = [%{input: input, output: output}]
    network_state = WorkerFixtures.initial_network_state

    args = %{data: %{location: :memory, source: data}}

    {:ok, _pid} = Worker.start_link(args, options)

    :ok    = Worker.predict(network_state, worker)
    result = Worker.get(worker)

    assert result == expected
  end
end