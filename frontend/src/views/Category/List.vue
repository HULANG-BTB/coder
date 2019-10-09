<template>
  <el-container>
    <el-main>
      <el-table
        :data="tableData"
        style="width: 100%"
        border
        fit
        @row-click="redirect"
      >
        <el-table-column
          label="编号"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.id }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="标题">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.title }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="分类/来源">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.source }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="提交"
          width="80">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.submit }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="正确"
          width="80">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.accepted }}</span>
          </template>
        </el-table-column>
      </el-table>
    </el-main>
    <el-footer>
      <el-pagination
        @size-change="handleSizeChange"
        @current-change="handlePageChange"
        :current-page="page"
        :page-sizes="[10, 20, 50, 100]"
        :page-size="limit"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total">
      </el-pagination>
    </el-footer>
  </el-container>
</template>

<script>
import {
  mapState,
  mapActions
} from 'vuex'

export default {
  data () {
    return {
      page: parseInt(this.$route.query.page) || 1,
      limit: parseInt(this.$route.query.limit) || 10,
      keyword: this.$route.query.keyword || '',
      type: this.$route.query.type || 'content'
    }
  },
  computed: {
    tableData () {
      return this.problemList.data
    },
    ...mapState(['problemList']),
    total () {
      return this.problemList.total
    }
  },
  mounted () {
    const query = this.buildQuery()
    this.getProblemList(query)
  },
  methods: {
    ...mapActions(['getProblemList']),
    handlePageChange (data) {
      this.page = data
      const query = this.buildQuery()
      this.$router.push({name: 'ProblemList', query: query})
      this.getProblemList(query)
    },
    handleSizeChange (data) {
      this.limit = data
      const query = this.buildQuery()
      this.$router.push({name: 'ProblemList', query: query})
      this.getProblemList(query)
    },
    redirect (obj) {
      this.$router.push({name: 'ProblemDetail', query: {id: obj.id}})
    },
    buildQuery () {
      const query = {
        page: this.page,
        limit: this.limit,
        type: this.type,
        keyword: this.keyword
      }
      return query
    }
  }
}
</script>

<style scoped>
.el-select {
  width: 150px;
}
</style>
